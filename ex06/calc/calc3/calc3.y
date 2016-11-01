// Yaccプログラムの例３：%unionの使用

%{
#include <stdio.h>
#include <math.h>
#include "calc-const.h"

extern int yylex(void);
int yyerror(const char *msg);
%}


// 属性名とその型の宣言
// トークンや非終端記号の属性が，異なる型をとれるようにする．
// 属性を保存する変数yylvalの型は共用体になる．
%union{
  // int型の属性名ivalの宣言 (NUMの属性)
  int ival;
  // double型の属性名rvalの宣言 (exprの属性)
  double rval;
  // CConst型の属性名opの宣言 (ADDOP,MULOPの属性)
  CConst op;
}


// トークンの宣言

%token <ival> NUM	  // NUMの属性の名前はival
%token <op> ADDOP MULOP	  // ADDOP,MULOPの属性名はop

/* 非終端記号の宣言				*/
/* 非終端記号の属性の型を，%unionの中の		*/
/* どれにするかを指定しないといけないので、	*/
/* 属性をもつ非終端記号には宣言が必要		*/

%type <rval> expr // exprの属性の名前はrval

// 非終端記号 calc は属性を持たないので宣言は必要ない


// 優先順位と結合規則の指定

%left ADDOP	 // ADDOP('+', '-')は左結合
%left MULOP	 // MULOP('*', '/', '%')は左結合


%%

calc : expr ';'		{ printf("%f\n",$1); }
     ;

expr : expr ADDOP expr
	// ADDOPの属性($2)がCaddなら加算，それ以外なら減算を行う．
	{ $$ = ($2 == Cadd) ? $1 + $3 : $1 - $3; }
        // exprの属性名はrvalなので，$$, $1, $3 はdouble型

     | expr MULOP expr
	// MULOPの属性($2)がCmultiplyなら乗算，Cdivideなら除算，
	// それ以外なら剰余算を行う．
	{ if ($2 == Cmultiply) $$ = $1 * $3;
          else if ($2 == Cdivide) $$ = $1 / $3;
	  else if ($2 == Cmodulo) $$ = fmod($1,$3); }
        // exprの属性名はrvalなので，$$, $1, $3 はdouble型

        // exprの属性名はrvalなので $$ はdouble型
        // NUMの属性名はIVALなので $1 はint型
        // したがって，$$ への $1 の代入にはキャストが必要
     | NUM		{ $$ = (double)$1; }

     | '(' expr ')'	{ $$ = $2; }

     ;

%%

// エラー処理関数
int yyerror(const char *msg)
{
  fprintf(stderr,"%s\n",msg);
  return 0;
}

main()
{
#if YYDEBUG
  extern int yydebug;	// Yaccプログラムのデバッグのための大域変数

  yydebug = 1;	// デバッグ表示付きの構文解析系を生成したいとき 1 を代入
#endif

  yyparse();
}


