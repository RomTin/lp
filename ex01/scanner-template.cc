using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

*******************************************************************/

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "const.h"
#include "scanner.h"
#include "error.h"
#include "y.tab.h"


// 定数の定義
#define FOREVER	1

/*	          */
/* 文字判定マクロ */
/*		  */

// 空白文字なら真
#define isWhiteSpace(c)	(c == ' ' || c == '\t' || c == '\n')

// ファイル内部だけで有効な関数のプロトタイプ宣言

static int getIdentifier(int c);
static int getCharacter(void);

// プログラム全体で有効な変数

int lineNo;	// 処理中の行の行番号(scaner.ccとerror.ccで使用)

// ファイル内部だけで有効な変数

static FILE *srcFilePointer;	// 原始プログラムのファイルディスクリプタ
static int currentChar;		// 先読み文字バッファ

#ifdef YYDEBUG
extern int yydebug;
#endif

/* 字句解析系を初期化する                              */
/*   filename: 原始プログラム名                        */
/*   返り値: なし                                      */
/*   副作用:   srcFilePointer にファイルポインタを代入 */
void initializeScanner(char *filename)
{
}


/* 字句読み取りモジュール                                */
/* 返り値: トークンを表す定数                            */
/* 副作用: 共用体 yylval に、必要に応じて属性を代入      */
/* 概要:   原始プログラムから文字をよみ，字句を切り出す．*/
/*         読み込んだ文字に応じてトークンの種類を決定し，*/
/*         トークンを返す．またトークンの属性があれば    */
/*         それをyylvalに格納する．                      */
int yylex()
{
 START:
  // 空白の読み飛ばし
  while (isWhiteSpace(currentChar))  {
    currentChar = getCharacter();
  }
  // この時点では currentChar には空白以外の文字が入っている

  // 識別子の取得
  if (currentCharが英字か)  {
    return getIdentifier(currentChar);

    ここに，以下の字句を読み取る処理とコメントを読み飛ばす処理を書く。
    （処理する順番は任意でよい）
    ・加減算演算子（+と-）
    ・乗除算演算子（*と/と%）
    ・論理演算子のうち&&と||

  // ファイルの終わりを表すEOFを読んだとき
  else if (currentChar == EOF)  {
    return EOF;
  }
  // その他の文字は不正な文字なのでエラー
  else  {
    compileError(EIllegalChar,currentChar,currentChar);
  }
}


// 識別子を取得する
//   c: 識別子の１文字目（英字）
//   返り値: トークン ID
//   副作用: yylval.symbol に字句へのポインタを代入
static int getIdentifier(int c)
{
    ここで，識別子の字句を読み取る有限オートマトンをシミュレートする．
    字句を保存するための局所変数を用意すること．
    字句へのポインタを yylval.symbol に代入し，識別子のトークンを返す．

  yylval.symbol = グローバル変数 yylval に字句を保存
                  yylval.symbol の型は y.tab.h を参照のこと．
  return ID;
}

// 文字読み取りモジュール
//  返り値: ファイルから読んだ文字
//  副作用: 改行文字を読んだとき lineNo が1増加
static int getCharacter()
{
}
