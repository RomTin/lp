// Yaccプログラムの例４：%precの使用

%{
#include <stdio.h>
#include <math.h>
#include "calc-const.h"

extern int yylex(void);
int yyerror(const char *msg);
%}


// 属性名とその型の宣言
%union{
  // int型の属性名ivalの宣言 (NUMの属性)
  int ival;
  // double型の属性名rvalの宣言 (exprの属性)
  double rval;
  // CConst型の属性名opの宣言 (ADDOP,MULOP,SIGNOPの属性)
  CConst op;
}


// トークンの宣言

%token <ival> NUM
%token <op> ADDOP MULOP SIGNOP	// ADDOP,MULOP,SIGNOPの属性名はop


// 非終端記号の宣言

%type <rval> expr	// exprの属性名はrval


// 優先順位と結合規則の指定

%left ADDOP	 // ADDOP('+', '-')は左結合
%left MULOP	 // MULOP('*', '/', '%')は左結合
%nonassoc SIGNOP // SIGNOP('+', '-')は結合性なし
                 //     （'+' '-' のように続けて現れるとエラーになる）

%%

calc : expr ';'		{ printf("%f\n",$1); }
     ;

expr : expr ADDOP expr
	// ADDOPの属性($2)がCaddなら加算，それ以外なら減算を行う．
	{ $$ = ($2 == Cadd) ? $1 + $3 : $1 - $3; }

     | expr MULOP expr
	// MULOPの属性($2)がCmultiplyなら乗算，Cdivideなら除算，
	// それ以外なら剰余算を行う．
	{ if ($2 == Cmultiply) $$ = $1 * $3;
          else if ($2 == Cdivide) $$ = $1 / $3;
	  else if ($2 == Cmodulo) $$ =fmod($1, $3); }

     // ADDOPをSIGNOPとして使用するには，%precを使う．
     | ADDOP expr %prec SIGNOP
        // ADDOPの属性($1)がCaddなら$2の属性値を，
        // そうでない(Csubtract)なら$2の属性値を符号反転したものを
        // exprの属性値とする．
	{ $$ = ($1 == Cadd) ? $2 : -$2; }
     | NUM		{ $$ = (double)$1; }
     | '(' expr ')'	{ $$ = $2; }
     ;

%%

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


