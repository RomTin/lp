/*********************************************
*   y.tab.h: Yaccが生成するヘッダファイル    *
*            トークンのための情報をもつ      *
*            （課題１，２専用）              *
*********************************************/

// トークンの属性を格納するための共用体 YYSTYPEの定義

/* 共用体は，構造体と同様にメンバをもつ．
   op, symbol, num がこの共用体のメンバである．
   ただし，構造体と異なり，共用体のメンバは
   すべて同じメモリを共有する．
   この共用体の場合，string * 型のメンバ symbol や
   CConst 型のメンバ op は同じメモリに割り当てられる．
   そのため、symbol と op が同時に有効になることはない．
   共用体では，構造体と同様にして . や -> を使って
   メンバにアクセスできる．ただし，共用体では
   実際に正しく格納されているメンバはつねに一つだけ
   なので，共用体をアクセスする側は，現在どのメンバが
   共用体に格納されているのかを知っていなければならない．*/

typedef union YYSTYPE {
  CConst op;		// 演算子を表す定数
  string *symbol;	// 識別子名へのポインタ
  int num;		// 数
} YYSTYPE;		// この共用体型に別名 YYSTYPE を与える


// トークンの定数を定義

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     NUM = 259,
     VAR = 260,
     FUNC = 261,
     COMM = 262,
     ADDOP = 263,
     MULOP = 264,
     RELOP = 265,
     LOGOP = 266,
     ULOGOP = 267,
     SIGNOP = 268,
     IF = 269,
     ELSIF = 270,
     ELSE = 271,
     WHILE = 272,
     REPEAT = 273,
     RETURN = 274
   };
#endif
#define ID 258
#define NUM 259
#define VAR 260
#define FUNC 261
#define COMM 262
#define ADDOP 263
#define MULOP 264
#define RELOP 265
#define LOGOP 266
#define ULOGOP 267
#define SIGNOP 268
#define IF 269
#define ELSIF 270
#define ELSE 271
#define WHILE 272
#define REPEAT 273
#define RETURN 274


// YYSTYPE型（上で定義した共用体型）の外部変数yylvalの宣言
// 字句解析系の関数 yylex()は、yylval（のメンバ）に属性を
// 代入して、構文解析系の関数 yyparse() に属性を渡す。

extern YYSTYPE yylval;
