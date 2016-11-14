/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INUM = 259,
     RNUM = 260,
     ADDOP = 261,
     MULOP = 262,
     RELOP = 263,
     LOGOP = 264,
     ULOGOP = 265,
     SIGNOP = 266,
     IF = 267,
     ELSIF = 268,
     ELSE = 269,
     WHILE = 270,
     REPEAT = 271,
     RETURN = 272,
     VOID = 273,
     INT = 274,
     REAL = 275
   };
#endif
/* Tokens.  */
#define ID 258
#define INUM 259
#define RNUM 260
#define ADDOP 261
#define MULOP 262
#define RELOP 263
#define LOGOP 264
#define ULOGOP 265
#define SIGNOP 266
#define IF 267
#define ELSIF 268
#define ELSE 269
#define WHILE 270
#define REPEAT 271
#define RETURN 272
#define VOID 273
#define INT 274
#define REAL 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 43 "../smplc.y"

  CConst op;            // 演算子を表す定数
  string *symbol;       // 識別子名へのポインタ
  VarEntry *var;        // 変数エントリへのポインタ
  STree *tree;          // 構文木へのポインタ
  ExprTree *expression; // 式の構文木へのポインタ
  int inum;             // 整数
  double rnum;          // 実数
  Code *code;           // 中間コードへのポインタ
  CondList *condlist;   // 条件と文リストのペアの列
  CondTree *condition;  // 条件の構文木へのポインタ
  Type type;            // 変数の型
  int loc;              // 番地



/* Line 1685 of yacc.c  */
#line 108 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


