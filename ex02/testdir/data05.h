/**************************************************
 テストデータ５
  正常ケース(文字)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "  'A''c''''";


// トークン
int tokens[] = {
  INUM, INUM, INUM, EOF };		// 1行目

// 識別子の字句
const char *ids[] = { };

// 整数(文字)
int inums[] = {   'A', 'c', '\'' };	// 1行目

// 実数
double rnums[] = { };

// 演算子の種別(const.hを参照)
int ops[] = { };
