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
    "宣言されていない変数%sを使用しています",
    "宣言されていない手続き%sを使用しています",
    "宣言された手続き%sの定義がありません",
    "変数%sは既に宣言されています",
    "手続き%sは既に宣言されています",
    "手続き%sは既に定義されています",
    "識別子%sは変数として既に宣言されています",
    "識別子%sは手続きとして既に宣言されています",
    "識別子%sは手続きではなく変数です",
    "識別子%sは変数ではなく手続きです",
    "識別子%sはコマンドではなく関数です",
    "識別子%sは関数ではなくコマンドです",
    "文字定数は１文字しか許されません",
    "予期しないファイルの終りを検出しました",
    "手続き%sの引数は%d個でなく%d個必要です",
    "手続き%sは%sではなく%sとして宣言されています",
    "コマンド%sがreturnで値を返しています",
    "関数%sがreturnで値を返していません",
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

