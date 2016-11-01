using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

  s1220091 国分佑太朗
  s1220228 海老原圭吾
  s1220233 小松凌也
  s1220244 向佐裕貴

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
static int getAddOp(int c); //加減算演算子のトークンを返却するユーザー定義関数
static int getMulOp(int c); //乗算・剰余算演算子のトークンを返却するユーザー定義関数
static int getLogOp(int c); //論理演算子のトークンを返却するユーザー定義関数

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
  FILE *fp;

  fp = fopen(filename, "r");

  // fp == NULL の時,ファイルを開くのに失敗している
  if (fp == NULL) {
    errorExit(EFileNotFound, filename);
  }

  // ファイルポインタを保存する
  srcFilePointer = fp;

  // LineNoを初期化する(開始行は1-origin)
  lineNo = 1;

  currentChar = getCharacter();

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
  if (isalpha(currentChar)/*が英字か*/)  {
    return getIdentifier(currentChar);

    //加減算演算子を読んだとき、ユーザー定義関数getAddOpをコールする
  }else if(currentChar == '+' || currentChar == '-') {
    return getAddOp(currentChar);

    //乗算、剰余算演算子を読んだとき、ユーザー定義関数getMulOpをコールする
  }else if(currentChar == '*' || currentChar == '%') {
    return getMulOp(currentChar);

    //除算演算子を読んだとき
    //コメントの読み飛ばし処理もこの中で行われる
  }else if(currentChar == Cdivide) {
    // 次の文字を取得
    currentChar = getCharacter();
    // 次の文字が \ でなければ，除算演算子で確定
    if (currentChar != Cdivide) {
      //yylval.opに論理演算子を代入
      yylval.op = (CConst)Cdivide;
      return MULOP;
    } 
    // 次の文字がコメントの場合
    else {
      // 改行文字かEOFが現れるまで読み続ける
      while(currentChar != EOF && currentChar != '\n') { 
        currentChar = getCharacter();
      }
      // 離脱
      goto START;
    }

    //論理演算子を読んだとき、ユーザー定義関数getLogOpをコールする
  }else if(currentChar == '&' || currentChar == '|') {
    return getLogOp(currentChar);

    // ファイルの終わりを表すEOFを読んだとき
  } else if (currentChar == EOF)  {
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
  /*
     ここで，識別子の字句を読み取る有限オートマトンをシミュレートする．
     字句を保存するための局所変数を用意すること．
     字句へのポインタを yylval.symbol に代入し，識別子のトークンを返す．
     */

  //strは字句を保存するための局所変数
  string str;

  //英字か判定
  if (isalpha(c)){
    str+=c;
    currentChar=getCharacter();//先読みバッファに追加
    c=currentChar;//字句先頭文字を更新

    //数字か英字であればループ
    while (isalnum(c)){
      str+=c;
      currentChar=getCharacter();//先読みバッファに追加
      c=currentChar;//字句先頭文字を更新
    }
  }

  yylval.symbol = new string(str);/*グローバル変数 yylval に字句を保存
                                    yylval.symbol の型は y.tab.h を参照のこと．*/
  return ID;
}

// 文字読み取りモジュール
//  返り値: ファイルから読んだ文字
//  副作用: 改行文字を読んだとき lineNo が1増加
static int getCharacter()
{
  char loadChar;
  // ファイルから1文字読む
  loadChar = fgetc(srcFilePointer);
  // それが改行コードならば，行番号を1つ増やす
  if (loadChar == '\n') {
    lineNo = lineNo + 1;
  }

  return loadChar;
}

// 加減算演算子'+'または'-'を取得する
//   c: 加減算演算子が期待される文字 '+'または'-'
//   返り値: トークン ADDOP
//   副作用: yylval.op に'+'ならCadd('+'の文字コード)、'-'ならCsubtract('-'の文字コード)を代入
static int getAddOp(int c){

  // 加減算演算子であれば取得し、そうでなければコンパイルエラー
  if (c == Cadd || c == Csubtract) {
    // CaddとCsubtractは演算子の文字コードそのままなので、直接代入できる。
    yylval.op = (CConst)c;

    // 全てのトークンの取得で先読みをする方針なので一文字先読みバッファに取得
    currentChar = getCharacter();

    return ADDOP;
  } else {
    // 加減算演算子でなければコンパイルエラー
    compileError(EIllegalChar, c, c);
  }
}

// 乗除算演算子の内、'*'または'%'を取得する
//   c: 乗除算演算子が期待される文字 '*'または'%'
//   返り値: トークン MULOP
//   副作用: yylval.op に'*'ならCmultiply('*'の文字コード)、'%'ならCmodulo('%'の文字コード)を代入
static int getMulOp(int c){

  // 乗除演算子であれば取得し、そうでなければコンパイルエラー
  if (c == Cmultiply || c == Cmodulo) {
    // CmultiplyとCmoduloは演算子の文字コードそのままなので、直接代入できる。
    yylval.op = (CConst)c;

    // 全てのトークンの取得で先読みをする方針なので一文字先読みバッファに取得
    currentChar = getCharacter();

    return MULOP;
  } else {
    // 乗除算演算子でなければコンパイルエラー
    compileError(EIllegalChar, c, c);
  }
}


// 論理演算子を取得
//    c: 論理演算子の一文字目、'&'または'|'
//    返り値: トークン名 LOGOP
//    副作用: yylval.op に各論理演算子の文字コード'%'(Cand)または'|'(Cor)を代入
static int getLogOp(int c){

  //後続の文字を読み込んでおく
  currentChar = getCharacter();
  //一文字目が&のケース
  if(c =='&'){
    if(!(currentChar == '&')){
      //後続が&ではないのでエラー
      compileError(EIllegalChar, currentChar, currentChar);
    }
    //一文字目が|のケース
  }else if(c == '|'){
    if(!(currentChar == '|')){
      //後続が|ではないのでエラー
      compileError(EIllegalChar, currentChar, currentChar);
    }
    //それ以外のケース（エラー）
  }else{
    //引数が&または|ではないのでエラー
    compileError(EIllegalChar, c, c);
  }

  //yylval.opに論理演算子を代入
  yylval.op = (CConst)c;

  // 先読み
  currentChar = getCharacter();

  //論理演算子のトークン名を返却
  return LOGOP;
}
