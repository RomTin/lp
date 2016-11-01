/***************************************************
*  error.h: error.cc のインタフェース・ファイル    *
*                                                  *
***************************************************/

#ifndef __ERROR_H__
#define __ERROR_H__


#include <stdarg.h>	// 可変個の引数をもつ関数のためのインクルードファイル

// エラーの種類を表す定数
enum Error {
  EFileNotFound,	// 原始プログラムのファイルが見つからない
  EIllegalChar,		// 不正な文字を読み込んだ
  EIllegalExpValue,	// 式の値が０以下
  EParseError		// 構文エラー
};

// error.ccで定義されている関数のプロトタイプ宣言

void compileError(Error id, ...);	// コンパイルエラーの処理
void errorExit(Error id, ...);		// それ以外のエラーの処理
void setFileName(char *name);		// ファイル名の保存


#endif
