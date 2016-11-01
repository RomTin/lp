/**************************************************
 テストデータ３３
   正常ケースのテスト(統合版)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "  var[,comm varcomm;2.5E3void(func}-FUnC\n\
real+cD5else10qg2ZwQ)50funcvar   while 	  whileif\twhile!return\n\
    \trepeat]0.1e-5elsif'A''c''''if2elsif,else*\n\
  0else1 50.2return0{if&&\t70.82E-03{ret 1.e+10int//12//5 \n\
urn\t25.5E+5!!=IF%1.REPEAT||While vOId elSE\n\
<<=>====!=>/05.e10\n\
002598";


// トークン
int tokens[] = {
  ID, '[', ',', ID, ID, ';', RNUM, VOID, '(', ID, '}', ADDOP, ID,   // 1行目
  REAL, ADDOP, ID, ')', INUM, ID, WHILE, ID, WHILE, ULOGOP, RETURN, // 2行目
  REPEAT, ']', RNUM, ELSIF, INUM, INUM, INUM, ID, ',', ELSE, MULOP, // 3行目
  INUM, ID, RNUM, ID, '{', IF, LOGOP, RNUM, '{', ID, RNUM, INT,	    // 4行目
  ID, RNUM, ULOGOP, RELOP, ID, MULOP, RNUM, ID, LOGOP, ID, ID, ID,  // 5行目
  RELOP, RELOP, RELOP, RELOP, '=', RELOP, RELOP, MULOP, RNUM,	    // 6行目
  INUM, EOF };							    // 7行目


// 識別子の字句
const char *ids[] = {
  "var", "comm", "varcomm", "func", "FUnC",		// 1行目
  "cD5else10qg2ZwQ", "funcvar", "whileif", 		// 2行目
  "if2elsif",						// 3行目
  "else1", "return0", "ret",				// 4行目
  "urn", "IF", "REPEAT", "While", "vOId", "elSE" };	// 5行目


// 整数
int inums[] = {
  50,			// 2行目
  'A', 'c', '\'',	// 3行目
  0,			// 4行目
  2598 };		// 7行目

// 実数
double rnums[] = {
  2.5E3,			// 1行目
  0.1e-5,			// 3行目
  50.2,	70.82E-03, 1.e+10,	// 4行目
  25.5E+5, 1.,			// 5行目
  05.e10 };			// 6行目

// 演算子の種別(const.hを参照)
int ops[] = {
  Csubtract,						// 1行目
  Cadd, Cnot,						// 2行目
  Cmultiply,						// 3行目
  Cand,							// 4行目
  Cnot, CnotEqual, Cmodulo, Cor,			// 5行目
  ClessThan, ClessThanOrEqual, CgreaterThanOrEqual,	// 6行目(1)
  Cequal, CnotEqual, CgreaterThan, Cdivide };			// 6行目(2)
