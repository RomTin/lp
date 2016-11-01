/**************************************************
 テストデータ２
   正常ケース(getNumber()が整数と実数を読む)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "5.8E10 2.5E02 20 0.1e-5 50.275 00 705.82E-03\n\
\t25.5E+5 05.e10 31.8 2.38E6 8.E-5 25.";

// トークン
int tokens[] = {
  RNUM, RNUM, INUM, RNUM, RNUM, INUM, RNUM,	// 1行目
  RNUM, RNUM, RNUM, RNUM, RNUM, RNUM, EOF };	// 2行目

// 識別子の字句
const char *ids[] = { };

// 整数
int inums[] = {
  20, 0 };			// 1行目

// 実数
double rnums[] = {
  5.8e10, 2.5e2, 0.1e-5, 50.275, 705.82e-03,		// 1行目
  25.5e+5, 5.0e10, 31.8, 2.38e6, 8.0e-5, 25.0 };	// 2行目

// 演算子の種別(const.hを参照)
int ops[] = { };
