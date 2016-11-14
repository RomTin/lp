/***************************************************
*  error.h: error.cc のインタフェース・ファイル    *
*                                                  *
***************************************************/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <string>
#include <stdarg.h>	// 可変個の引数をもつ関数のためのインクルードファイル
#include "const.h"

// エラーの種類を表す定数
enum Error {
  EFileNotFound,	// 原始プログラムのファイルが見つからない
  EVarNotDeclared,	// 変数が未宣言
  EProcNotDeclared,	// 手続きが未宣言
  EProcNotDefined,	// 手続きが未定義
  EVarDuplicated, 	// 変数の二重宣言
  EProcDuplicated,	// 手続きの二重宣言
  EProcDefDuplicated,	// 手続きの二重定義
  EAlreadyAsVar,	// 既に変数として宣言されている
  EAlreadyAsProc,	// 既に手続きとして宣言されている
  EDeclaredAsVar,	// 変数を手続きとして使用
  EDeclaredAsProc,	// 手続きを変数として使用
  EDeclaredAsComm,	// コマンドとして宣言されている
  ETooLongCharacter,	// 文字が長過ぎる
  EUnexpectedEOF,	// 予期しないEOF
  EIllegalReal,         // 不正な実数の字句
  EParamNumMismatch,	// 引数個数の不一致
  EVoidVariable,        // 変数の型が void
  EDeclaredAsSimpleVar, // 単純変数を配列変数として使用
  EDeclaredAsArray,     // 配列変数を単純変数として使用
  EIllegalSize,         // 配列のサイズが不正
  EIndexTypeMismatch,	// 配列のインデックスが整数型でない
  EReturnValue,		// コマンドが値を返している
  ENotReturnValue,	// 関数が値を返さない
  ERepeatTypeMismatch,  // repeat文の回数の型の不一致
  EIllegalChar,		// 不正な文字を読み込んだ
  EParseError		// 構文エラー
};

// error.ccで定義されている関数のプロトタイプ宣言

void compileError(Error id, ...);	// コンパイルエラーの処理
void errorExit(Error id, ...);		// コンパイルエラー以外のエラー処理
void setFileName(char *name);		// ファイル名の保存
int yyerror(char *msg);		// Yaccが生成した構文解析系用のエラー処理関数
string &typeString(Type type);		// 型を表す文字列を返す

#endif
