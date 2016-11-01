// Yaccプログラムの例：０回以上の繰り返し

%{
#include <ctype.h>
#include <stdio.h>

extern int yylex(void);
int yyerror(const char *msg);
%}

%token NUM	// トークン NUM の宣言

%%

// line の翻訳規則
line : 			{ printf("スタート！\n"); }
     | line NUM ';'	{ printf("%d\n",$2); }
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

