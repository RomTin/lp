/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lf-scanner.h"
#include "token.h"
#include "error.h"
#include "parse.h"


// static関数のプロトタイプ宣言
static bool parseLF(void);
static bool parseLF2(bool);
static bool parseNoImpl(void);
static bool parseNoImpl2(bool);
static bool parseSimpleLF(void);
static void match(int x);

// トークンを保存するstatic変数
static int token;


// 構文解析系のトップレベル関数
//   引数: なし
//   返り値: 解析した論理式の真理値
//   副作用: なし
bool parse()
{
  bool b;

  token = getToken();	// 最初のトークンを先読み
  b = parseLF();	// 構文解析の開始

  // EOFでなければ余分なトークンが残っていたことになるのでエラー
  if (token != EOF)  {
    compileError(ETooMuchTokens,getLexeme(token));
    // getLexeme() のプロトタイプ宣言は lf-scanner.h にある
  }
  else
    return b;
}

/** ボーナス点を狙うチームはここから parseNoImpl2()の定義までコメントアウトし、
    手続きを統合した parseLF() と parseNoImp() を新たに定義する。
**/

// 「論理式」の構文解析を行い，その真理値を返す
//   引数: なし
//   返り値: 解析した論理式の真理値
//   副作用: なし
bool parseLF()
{
}

// 「論理式」の構文解析を行い，その真理値を返す
//   引数: トークンIMPLの前に現れる論理式の真理値
//   戻り値: 引数と構文解析の結果から決まる真理値
//   副作用: なし
bool parseLF2(bool b)
{
}

// 「含意無し論理式」の構文解析を行い，その真理値を返す
//   引数: なし
//   返り値: 解析した含意無し論理式の真理値
//   副作用: なし
bool parseNoImpl()
{
}

// 「含意無し論理式２」の構文解析を行い，その真理値を返す
//   引数: トークンAND, ORの前に現れる論理式の真理値
//   戻り値: 引数と構文解析の結果から決まる真理値
//   副作用: なし
bool parseNoImpl2(bool b)
{
}
/** ボーナス点を狙うチームは、parseLF()の定義からここまでをコメントアウトする **/

// 「単純論理式」の構文解析を行い，その真理値を返す
//   引数: なし
//   返り値: 解析した単純論理式の真理値
//   副作用: なし
bool parseSimpleLF()
{
}

// 読み込んだトークンが期待しているトークンと一致しているかどうか調べる
//   x: 期待しているトークン
//   返り値: なし
//   副作用: トークンが一致したら，token に次のトークンが格納される．
//           一致しなければエラー終了し，呼び出し側には戻らない．
void match(int x)
{
  if (x == token)  {
    token = getToken();		// 一致すれば次のトークンを先読み
  }
  // EOF を読み込んだ
  else if (token == EOF) {
    compileError(EUnexpectedEOF);
  }
  // EOFではないが，x と異なるトークンを読み込んだ
  else
    compileError(EIllegalToken,getLexeme(x),getLexeme(token));
}
