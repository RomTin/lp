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
  ETooMuchTokens,	// トークンが多すぎる
  EUnexpectedEOF,	// 予期しないファイルの終りに遭遇した
  ENotSimpleLF,		// 単純論理式ではない構文要素を読んだ
  EIllegalToken		// 不正なトークンを読んだ
};

// error.ccで定義されている関数のプロトタイプ宣言

void compileError(Error id, ...);	// コンパイルエラーの処理
void errorExit(Error id, ...);		// それ以外のエラーの処理
void setFileName(char *name);		// ファイル名の保存


#endif
