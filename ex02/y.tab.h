/*********************************************
*   y.tab.h: Yaccが生成するヘッダファイル    *
*            トークンのための情報をもつ      *
*            （課題７専用）                  *
*********************************************/

// トークンの属性を格納するための共用体 YYSTYPEの定義

/* 共用体は，構造体と同様にメンバをもつ．
   op, symbol, inum, rnum がこの共用体のメンバである．
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
  int inum;		// 整数
  double rnum;		// 実数
} YYSTYPE;		// この共用体型に別名 YYSTYPE を与える


// トークンの定数を定義

#define ID 258
#define INUM 259
#define RNUM 260
#define VOID 261
#define INT 262
#define REAL 263
#define ADDOP 264
#define MULOP 265
#define RELOP 266
#define LOGOP 267
#define ULOGOP 268
#define SIGNOP 269
#define IF 270
#define ELSIF 271
#define ELSE 272
#define WHILE 273
#define REPEAT 274
#define RETURN 275


// YYSTYPE型（上で定義した共用体型）の外部変数yylvalの宣言
// 字句解析系の関数 yylex()は、yylval（のメンバ）に属性を
// 代入して、構文解析系の関数 yyparse() に属性を渡す。

extern YYSTYPE yylval;
