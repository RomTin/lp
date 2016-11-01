/****************************************************************
   error.cc  エラー処理を行う

****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// 外部変数
extern int lineNo;		// 処理中の行番号(scaner.ccで定義)

// ファイル内だけで有効な関数のプロトタイプ宣言

static void error(Error id, va_list ap);

// ファイル内だけで有効な変数

static const char *fileName;		// 原始プログラムのファイル名

// エラーメッセージ
static const char *errMsg[] =
  { "ファイルが見つかりません: %s",
    "%c(16進コード: %x)は不正な文字です",
    "式の値が０以下(%d)になりました",
    "構文エラーです",
  };

/* エラーメッセージを表示して終了			*/
/*   msg: エラーメッセージのフォーマット出力文字列	*/
/*   ...: フォーマット出力文字列の実引数		*/
void compileError(Error id, ...)
{
  va_list argptr;
  fprintf(stderr,"%s:%d:",fileName,lineNo);
  va_start(argptr,id);
  error(id,argptr);
}

// エラー処理を行う関数
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
