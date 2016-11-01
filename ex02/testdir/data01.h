/**************************************************
 テストデータ１
   正常ケース(getNumber()が整数を読む)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "10 0 1592 00 00135";


// トークン
int tokens[] = {
  INUM, INUM, INUM, INUM, INUM, EOF };	// 1行目


// 識別子の字句
const char *ids[] = { };

// 整数
int inums[] = {
  10, 0, 1592, 00, 135 };		// 1行目

// 実数
double rnums[] = { };

// 演算子の種別(const.hを参照)
int ops[] = { };
