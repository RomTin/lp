// Yaccプログラムの例２：優先順位と結合性の指定

%{
#include <stdio.h>
extern int yylex(void);
int yyerror(const char *msg);
%}

// トークンの宣言

%token NUM


// 優先順位と結合性の宣言

/* 下に行くほど優先順位が高い．  */
/* 結合性は以下のものが指定可能  */
/*     %left: 左結合             */
/*     %right: 右結合            */
/*     %nonassoc: 結合性なし     */

%left '+'	/* + は左結合 */
%left '*'	/* * は左結合 */

%%

// Yacc宣言部に %start がないときは，
// 最初の翻訳規則の : の左側にある非終端記号が
// 開始記号になる．したがって、このプログラムの
// 開始記号は calc になる．

/* calc の翻訳規則 */
calc : expr ';' 		{ printf("%d\n",$1); }
     ;

/* expr の翻訳規則 */
/* + と * についての規則がここに書かれていることに注意 */
expr : expr '+' expr		{ $$ = $1 + $3; }
     | expr '*' expr		{ $$ = $1 * $3; }
     | NUM			{ $$ = $1; }
     | '(' expr ')'		{ $$ = $2; }
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
  extern int yydebug;

  yydebug = 1;
#endif

  yyparse();
}

