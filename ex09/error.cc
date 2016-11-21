/****************************************************************
   error.cc  コンパイラのエラー処理を行う

****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// 外部変数
extern int lineNo;		// 処理中の行番号(scaner.ccで定義)

// ファイル内だけで有効な変数
static const char *fileName;	// 原始プログラムのファイル名

// エラーメッセージ
static const char *errMsg[] =
  { "ファイルが見つかりません: %s",
    "変数%sは宣言されていません",
    "手続き%sは宣言されていません",
    "宣言された手続き%sの定義がありません",
    "変数%sは既に宣言されています",
    "手続き%sは既に宣言されています",
    "手続き%sは既に定義されています",
    "識別子%sは変数として既に宣言されています",
    "識別子%sは手続きとして既に宣言されています",
    "識別子%sは手続きではなく変数です",
    "識別子%sは変数ではなく手続きです",
    "識別子%sは関数ではなくコマンドです",
    "文字定数は１文字しか許されません",
    "予期しないファイルの終りを検出しました",
    "実数の字句に%c(16進コード: %x)が不正に現れました",
    "手続き%sの引数は%d個でなく%d個必要です",
    "手続き%sの%d番目の引数の型が違います",
    "手続き%sの返り値の型が違います",
    "変数%sの型がvoid型です",
    "%sは配列ではありません",
    "%sは配列です",
    "配列%sのサイズが不正です",
    "配列%sのインデックスが整数型ではありません",
    "コマンド%sがreturnで値を返しています",
    "関数%sがreturnで値を返していません",
    "repeat文中の式の型がint型ではありません",
    "%c(16進コード: %x)は不正な文字です",
    "構文エラーです"
  };

// ファイル内部で有効な関数のプロトタイプ宣言
static void error(Error id, va_list ap);	// エラー処理用共通関数


/* コンパイルエラーメッセージを表示して終了		*/
/*   msg: エラーメッセージのフォーマット出力文字列	*/
/*   ...: フォーマット出力文字列の実引数		*/
void compileError(Error id, ...)
{
  va_list argptr;
  fprintf(stderr,"%s:%d:",fileName,lineNo);
  va_start(argptr,id);
  error(id,argptr);
}

// コンパイル以外のエラー処理を行う関数
void errorExit(Error id, ...)
{
  va_list argptr;

  va_start(argptr,id);
  error(id,argptr);
}

// エラー処理用共通関数
static void error(Error id, va_list ap)
{
  vfprintf(stderr,errMsg[id],ap);
  fputc('\n',stderr);
  va_end(ap);
  exit(2);
}

// ファイル名をstatic変数fileNameに保存
void setFileName(char *name)
{
  fileName = name;
}

// Yaccが生成する構文解析系が用いるエラー処理関数 yyerror()の定義
int yyerror(char *msg)
{
  // compileErrorを呼び出して終了
  compileError(EParseError);
  // compileError() の中で終了するので，ここへは来ない．
  // error.ccがコンパイルできるようにするためだけに return が必要
  return 0;
}

// 型を表す文字列
static string typeStr[] = { "void", "int", "real" };

string &typeString(Type type)
{
  int index;

  switch (type)  {
  case TVoid: index = 0; break;
  case TInt:  index = 1; break;
  case TReal: index = 2; break;
  }
  return typeStr[index];
}
