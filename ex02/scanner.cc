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

/*		  */
/* 文字判定マクロ */
/*		  */

// 空白文字なら真
#define isWhiteSpace(c)	(c == ' ' || c == '\t' || c == '\n')

// ファイル内部だけで有効な関数のプロトタイプ宣言

static int getIdentifier(int c);
static int getNumber(int c);
static int isReservedWord(string);
static int getCharacter(void);

//ex01
static int getAddOp(int c); //加減算演算子のトークンを返却するユーザー定義関数
static int getMulOp(int c); //乗算・剰余算演算子のトークンを返却するユーザー定義関数
static int getLogOp(int c); //論理演算子のトークンを返却するユーザー定義関数

//ex02
static int getEqOp(int c); //単行論理演算子・関係演算子のトークンを返却するユーザー定義関数
static int getINUM(int c);
static int getSingleToken(int c);

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

    // 識別子または予約語の取得
    if (isalpha(currentChar)/*が英字か*/)  {
        return getIdentifier(currentChar);
    }
    // 整数と実数の取得
    else if (isdigit(currentChar))  {
        return getNumber(currentChar);
    }
    //加減算演算子を読んだとき、ユーザー定義関数getAddOpをコールする
    else if(currentChar == '+' || currentChar == '-') {
        return getAddOp(currentChar);
    }
    //乗算、剰余算演算子を読んだとき、ユーザー定義関数getMulOpをコールする
    else if(currentChar == '*' || currentChar == '%') {
        return getMulOp(currentChar);
    }
    //除算演算子を読んだとき
    //コメントの読み飛ばし処理もこの中で行われる
    else if(currentChar == Cdivide) {
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
    }
    //論理演算子を読んだとき、ユーザー定義関数getLogOpをコールする
    else if(currentChar == '&' || currentChar == '|') {
        return getLogOp(currentChar);
    }
    //関係比較演算子を読んだとき、ユーザー定義関数getEqOpをコールする
    else if(currentChar == '>' || currentChar == '<' || currentChar == '=' || currentChar == '!'){
        return getEqOp(currentChar);
    }
    //シングルクォートを読んだとき、ユーザー定義関数getINUMをコールする
    else if(currentChar == '\''){
        return getINUM(currentChar);
    }
    //括弧などその他の文字を読んだとき、ユーザー定義関数getSignleTokenをコールする
    else if(currentChar == '(' || currentChar == ')' || currentChar == '[' || currentChar == ']' || currentChar == '{' || currentChar == '}' || currentChar == ';' || currentChar == ','){
        return getSingleToken(currentChar);
    }
    // ファイルの終わりを表すEOFを読んだとき
    else if (currentChar == EOF)  {
        return EOF;
    }
    // その他の文字は不正な文字なのでエラー
    else  {
        compileError(EIllegalChar,currentChar,currentChar);
    }
}


/* 字句が予約語かどうか判定する                               */
/*   lexim: 字句                                              */
/*   返り値: トークンを表す定数（leximが予約語を表す字句なら，*/
/*           その予約語のためのトークンを表す定数を，         */
/*           それ以外なら識別子トークンを表す定数を返す）     */
static int isReservedWord(string lexim)
{
  static struct rword {
    int token;
    string lexim;
  } reservedWordTable[] = { { INT,    "int" },
    { REAL,   "real" },
    { VOID,   "void" },
    { IF,     "if" },
    { ELSIF,  "elsif" },
    { ELSE,   "else" },
    { WHILE,  "while" },
    { REPEAT, "repeat" },
    { RETURN, "return" } };
  // size は予約語表 reservedWordTable の大きさ
  const int size = sizeof(reservedWordTable)/sizeof(struct rword);

  /*字句 lexim が予約語なら，対応する予約語のトークンを返す．
    そうでなければ，識別子トークン ID を返す．
    */

  // reservedWordTable内に一致するものがあればそのtokenを返す。
  for (int i = 0; i < size; i ++) {
    // 比較対象が予約語と一致すればそのトークンを返す。
    if(lexim == reservedWordTable[i].lexim) {
      return reservedWordTable[i].token;
    }
  }

  // なければID
  return ID;
}


/* 識別子を取得する                                 */
/*   c: 識別子の１文字目（英字）                    */
/*   返り値: トークン（ID か予約語のトークン）      */
/*   副作用: yylval.symbol に字句へのポインタを代入 */
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

  // 取得した字句が予約語かどうかを判定し、結果のトークンを取得。
  int token = isReservedWord(str);

  // 判定した結果予約語でなければyylvalに属性を設定
  if(token == ID) {
    yylval.symbol = new string(str);/*グローバル変数 yylval に字句を保存
                                    yylval.symbol の型は y.tab.h を参照のこと．*/
  }

  return token;
}

/* 整数または実数を取得する                                          */
/*   c: 字句の１文字目（数字）                                       */
/*   返り値: トークンINUM か RNUM                                    */
/*   副作用: yylval.inum か yylval.rnum に字句が表す整数か実数を代入 */
static int getNumber(int c)
{
    //整数・実数値に変換するための文字列を格納する変数
    string retVal = "";

    //引数が数字でなければエラー
    if(!('0' <= c && c <= '9')){
        compileError(EIllegalReal, c, c);
    }

    //整数部の読み取り
    while(1){
        //currentCharが数字である限りループ
        if(!('0' <= currentChar && currentChar <= '9')){
            break;
        }
        retVal += currentChar;
        //先読み
        currentChar = getCharacter();
    }

    //currentCharが'.'以外の文字のときretValは整数としてyylval.inumに格納
    if(currentChar != '.'){
        yylval.inum = atoi(retVal.c_str());
        return INUM;
    }
    //'.'のときはretValに繋げてretValを実数とみなして処理を続行
    else if(currentChar == '.'){
        retVal += currentChar;
        currentChar = getCharacter();
    }

    //少数部の読み取り
    while(1){
        //currentCharが数字である限りループ
        if(!('0' <= currentChar && currentChar <= '9')){
            break;
        }
        retVal += currentChar;
        //先読み
        currentChar = getCharacter();
    }

    if(!(currentChar == 'E' || currentChar == 'e')){
        //currentCharがE,eでなければretValを少数の実数としてyylval.rnumに格納
        yylval.rnum = atof(retVal.c_str());
        return RNUM;
    }else if(currentChar == 'E' || currentChar == 'e'){
        //E,eであるときretValは指数表記の実数となるので処理を続行
        retVal += currentChar;
        currentChar = getCharacter();
    }

    //'+'もしくは'-'を読み込んだときに指数の符号をそれに応じて変更する
    if(currentChar == '+'){
        //そのままでよい
        currentChar = getCharacter();
    }else if(currentChar == '-'){
        //'-'の場合はretValにつなげる
        retVal += currentChar;
        currentChar = getCharacter();
    }

    //指数表記の一文字目を読み取る
    if('0' <= currentChar && currentChar <= '9'){
        //数字なのでそのままつなげる
        retVal += currentChar;
        currentChar = getCharacter();
    }else{
        //数字ではないのでコンパイルエラー
        compileError(EIllegalReal, currentChar, currentChar);
    }

    //currentCharが数字である限りループ
    while(1){
        if(!('0' <= currentChar && currentChar <= '9')){
            //retValを指数表記の実数としてyylval.rnumに格納
            yylval.rnum = atof(retVal.c_str());
            return RNUM;
        }
        retVal += currentChar;
        //先読み
        currentChar = getCharacter();
    }

}


/* 文字読み取りモジュール                       */
/*  返り値: ファイルから読んだ文字              */
/*  副作用: 改行文字を読んだとき lineNo が1増加 */
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

//単行論理演算子'!'・関係演算子'>', ">=", '<', "<=", "==", "!=" を取得する
//   c: 単行論理演算子の1文字目か関係演算子の1文字目 '!', '>', '<', '='
//   返り値: 単行演算子ならトークン ULOGOP, 関係演算子ならトークン RELOP
//   副作用: yylval.op に'!'ならCnot('!'の文字コード)、
//                 '>'ならCgreaterThan('>'の文字コード)、
//                 '>='ならCgreaterThanOrEqual('>='の文字コード)、
//                 '<'ならClessThan('<'の文字コード)、
//                 '<='ならClessThanOrEqual('<='の文字コード)、
//                 '=='ならCequal('=='の文字コード)、
//                 '!='ならCnotEqual('!='の文字コード)を代入する
static int getEqOp(int c){
  //後続の文字を読み込んでおく
  //このときcurrentCharに期待されるのは'='かそうでないか
  currentChar = getCharacter();
  
  if(c == Cnot){//1文字目が'!'のケース
    if(!(currentChar == '=')){//単行論理演算子'!'のケース
      //yylval.opにCnotを代入
      yylval.op = (CConst)c;
      return ULOGOP;
    }else if(currentChar == '='){//関係演算子"!="のケース
      //yylval.opにCnotEqualを代入
      yylval.op = (CConst)CnotEqual;
      //先読みバッファの更新
      currentChar = getCharacter();
      return RELOP;
    }
  }
  else if(c == '>'){//1文字目が'>'のケース
    if(!(currentChar == '=')){//関係演算子'>'のケース
      //yylval.opにCgreterThanを代入
      yylval.op = (CConst)CgreaterThan;
      return RELOP;
    }else if(currentChar == '='){//関係演算子">="のケース
      //yylval.opにCgreaterThanOrEqualを代入
      yylval.op = (CConst)CgreaterThanOrEqual;
      //先読みバッファの更新
      currentChar = getCharacter();
      return RELOP;
    }
  }
  else if(c == '<'){//1文字目が'<'のケース
    if(!(currentChar == '=')){//関係演算子'<'のケース
      //yylval.opにClessThanを代入      
      yylval.op = (CConst)ClessThan;
      return RELOP;
    }else if(currentChar == '='){//関係演算子"<="のケース
      //yylval.opにClessThanOrEqualを代入
      yylval.op = (CConst)ClessThanOrEqual;
      //先読みバッファの更新
      currentChar = getCharacter();
      return RELOP;
    }
  }
  else if(c == '='){//1文字目が'='のケース
    if(!(currentChar == '=')){//関係演算子'='のケース
      //yylval.opに'='の文字コードを代入
      yylval.op = (CConst)c;
      return c;
    }else if(currentChar == '='){//関係演算子"=="のケース
      //yylval.opにCequalを代入
      yylval.op = (CConst)Cequal;
      //先読みバッファを更新
      currentChar = getCharacter();
      return RELOP;
    }
  }
  else{//上記以外のケースはエラー処理
    compileError(EIllegalChar, c, c);
  }
}
static int getINUM(int c){

  if ( c == '\'') {

  // クオートで囲まれていることを期待する任意の文字を読む
  int saveChar = currentChar = getCharacter();

  // EOF だった場合 = クオートで囲まれてないことが明らかの場合 = エラー
  if ( saveChar == EOF ){
      compileError(EUnexpectedEOF, saveChar, saveChar);
  }

  // 閉じクオートを読む
  currentChar = getCharacter();
  // クオートではない場合 = EOFだった場合
  if ( currentChar == EOF ){
      compileError(EUnexpectedEOF, currentChar, currentChar);
  } 
  // クオートではない場合 = クオートで1文字が囲まれていない場合 = エラー
  else if ( currentChar != '\'') {
      compileError(ETooLongCharacter, currentChar, currentChar);
  }

  // クオートで囲まれている文字をを格納
  yylval.inum = saveChar;

  // 先読み
  currentChar = getCharacter();

  return INUM;
  }

}

static int getSingleToken(int c){
  // 先読み
  currentChar = getCharacter();
  return c;
}
