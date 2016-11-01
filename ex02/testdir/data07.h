/**************************************************
 テストデータ７
  正常ケース(識別子と予約語)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "var[while varwhile void void2\n\
real 3.8e5int Int else 10if 2.5return RETURN  rEpEat\n\
elsif'a' elseif if2elsif re\n\
turn wHile IF 1.repeat whilE";

// トークン
int tokens[] = {
  ID, '[', WHILE, ID, VOID, ID,					// 1行目
  REAL, RNUM, INT, ID, ELSE, INUM, IF, RNUM, RETURN, ID, ID,	// 2行目
  ELSIF, INUM, ID, ID, ID,				 	// 3行目
  ID, ID, ID, RNUM, REPEAT, ID, EOF };				// 4行目

// 識別子の字句
const char *ids[] = {
  "var", "varwhile", "void2",				// 1行目
  "Int", "RETURN", "rEpEat",		 		// 2行目
  "elseif", "if2elsif",	"re",				// 3行目
  "turn", "wHile", "IF", "whilE" };			// 4行目

// 整数
int inums[] = {
  10,			// 2行目
  'a' };		// 3行目

// 実数
double rnums[] = {
  3.8e5, 2.5,			// 2行目
  1.0 };			// 4行目

// 演算子の種別(const.hを参照)
int ops[] = { };
