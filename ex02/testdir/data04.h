/**************************************************
 テストデータ４
  正常ケース(RELOP: ==, !=, ULOGOP, =)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "!!=<<=>====!=";


// トークン
int tokens[] = {
  ULOGOP, RELOP, RELOP, RELOP, RELOP, RELOP, '=', RELOP, EOF };	// 1行目

// 識別子の字句
const char *ids[] = { };

// 整数
int inums[] = { };

// 実数
double rnums[] = { };

// 演算子の種別(const.hを参照)
int ops[] = {
  Cnot, CnotEqual, ClessThan, ClessThanOrEqual,		// 1行目(1)
  CgreaterThanOrEqual, Cequal, CnotEqual, EOF };	// 1行目(2)
