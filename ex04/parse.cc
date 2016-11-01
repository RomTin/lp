/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

  s1220091 国分佑太朗
  s1220228 海老原圭吾
  s1220233 小松凌也
  s1220244 向佐裕貴

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

// 要素が集合に含まれているかどうか判別する関数
bool isContain(int token, int *tokenList, size_t list_size);

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
  // first(論理式)の配列
  int first_LF[] = {NOT, '(', TRUE, FALSE};

  // first(論理式)にtokenが含まれていれば構文解析を続け、
  // 含まれなければコンパイルエラー
  if (isContain(token, first_LF, 4)) {
    // 初めに、IMPLがあった場合に左辺値、ない場合は式全体の値になる真理値を取得。    
    bool left = parseNoImpl();
    // 論理式2に左辺値を適用した結果を返す。
    return parseLF2(left);
  // EOFを読んだ時
  } else if (token == EOF)  {
    compileError(EUnexpectedEOF);
  } else {
    compileError(ENotSimpleLF,getLexeme(token));
  }
}

// 「論理式」の構文解析を行い，その真理値を返す
//   引数: トークンIMPLの前に現れる論理式の真理値
//   戻り値: 引数と構文解析の結果から決まる真理値
//   副作用: なし
bool parseLF2(bool b)
{
  bool right;//右辺値の論理式の真理値
  int first_LF2[] = {IMPL};
  int first_close[] = {')'};
  if (isContain(token,first_LF2, 1)){//IMPLがあれば
    match(IMPL);
    //IMPLのあとの論理式の真理値を取得する 
    right = parseLF();
    goto calc;
  }
  //閉じカッコのケースでbを返却し、一つ上の関数でmatch(')')をするようにする
  else if(isContain(token, first_close, 1)){
    return b;
  } 
  return b;
calc:
  //引数と構文解析の結果から計算されるIMPLの真理値を返す
  if((b == true && right == true)||(b == false && right == true)||(b == false && right == false)){
    return true;
  }
  else if(b == true && right == false){
    return false;
  }
}

// 「含意無し論理式」の構文解析を行い，その真理値を返す
//   引数: なし
//   返り値: 解析した含意無し論理式の真理値
//   副作用: なし
bool parseNoImpl()
{
  // first(含意無し論理式)の配列
  int first_no_impl[] = {NOT, '(', TRUE, FALSE};

  // first(含意無し論理式)にtokenが含まれていれば構文解析を続け、
  // 含まれなければコンパイルエラー
  if (isContain(token, first_no_impl, 4)) {
    // 初めに、ANDまたはORがあった場合に左辺値、ない場合は式全体の値になる真理値を取得。    
    bool left = parseSimpleLF();
    // 含意無し論理式2に左辺値を適用した結果を返す。
    return parseNoImpl2(left);
  } else if (token == EOF)  {
    compileError(EUnexpectedEOF);
  } else {
    compileError(ENotSimpleLF,getLexeme(token));
  }
}

// 「含意無し論理式２」の構文解析を行い，その真理値を返す
//   引数: トークンAND, ORの前に現れる論理式の真理値
//   戻り値: 引数と構文解析の結果から決まる真理値
//   副作用: なし
bool parseNoImpl2(bool b)
{
  bool sim, left;
  int first_AND[]={AND};
  int first_OR[]={OR};
  int first_close[] = {')'};
  if(isContain(token,first_AND, 1)){//ANDがあれば
    match(AND);
    //ANDのあとの含意無し論理式の真理値を取得する
    sim = parseSimpleLF();
    left = b && sim;
    return parseNoImpl2(left);
  }
  else if(isContain(token,first_OR, 1)){//ORがあれば
    match(OR);
    //ORのあとの含意無し論理式の真理値を取得する
    sim = parseSimpleLF();
    left = b || sim;
    return parseNoImpl2(left);
  }
  //閉じカッコのケースで、一つ上の関数でmatch(')')をするようにする
  else if(isContain(token, first_close, 1)){
    return b;
  }
  return b;
}
/** ボーナス点を狙うチームは、parseLF()の定義からここまでをコメントアウトする **/

// 「単純論理式」の構文解析を行い，その真理値を返す
//   引数: なし
//   返り値: 解析した単純論理式の真理値
//   副作用: なし
bool parseSimpleLF()
{
  int first_not_simplelf[] = {NOT};
  int first_nest_lf[] = {'('};
  int first_true[] = {TRUE};
  int first_false[] = {FALSE};

  // 書き換え規則 単純論理式→ NOT 単純論理式 の場合，token ∈ first(NOT 単純論理式)
  if (isContain(token, first_not_simplelf, 1)) {
    match(NOT);
    // NOT なので，演算結果を反転させる
    return !parseSimpleLF();

  } 
  // 書き換え規則 単純論理式 →  (論理式) の場合 token ∈ first((論理式))
  else if (isContain(token, first_nest_lf, 1)) {
    match('(');
    // 論理式の構文解析を行う
    bool result = parseLF(); 
    match(')');
    return result;
  }
  // 書き換え規則 単純論理式 →  TRUE の場合 token ∈ first(TRUE)
  else if (isContain(token, first_true, 1)) {
    match(TRUE);
    return true;
  }
  // 書き換え規則 単純論理式 →  FALSE の場合 token ∈ first(FALSE)
  else if (isContain(token, first_false, 1)){
    match(FALSE);
    return false; 
  }
  // EOFを読んだ時
  else if (token == EOF)  {
    compileError(EUnexpectedEOF);
  } 
  else {
    compileError(ENotSimpleLF,getLexeme(token));
  }

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

// 指定された集合にトークンが含まれるかどうか判別する
bool isContain(int token, int *tokenList, size_t list_size){
  // tokenListの長さだけループをする
  for(int i = 0; i < list_size; i++){
    if(token == tokenList[i]){
      // 一致すればtrue
      return true;
    }
  }
  // 見つからなかったのでfalse
  return false;
}
