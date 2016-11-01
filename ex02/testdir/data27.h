/**************************************************
 課題１ テストデータ１
   scanner.c についての正常ケースのテスト
   (識別子の直後がEOFの場合)
**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "  var1 cat varcomm function ab\n\
cD5a10qg2ZwQ+-funcvar    	  whileif* %\n\
\n\
    \t/if2q elsifw \n\
  A2q+++/*\n\
\n\
q1if+k23 \tret\n\
urn// ab **+ **///if while return\n\
-/%\n\
+////+*&!//*/*\n\
 \t\t  aA23509&&\n\
    ||&&+B&&\n\
&&/||*||\n\
    \n\
\t\n\
a";


// トークン
int tokens[] = 
  { ID, ID, ID, ID, ID,				// 1行目
    ID, ADDOP, ADDOP, ID, ID, MULOP, MULOP, 	// 2行目
						// 3行目
    MULOP, ID, ID,				// 4行目
    ID, ADDOP, ADDOP, ADDOP, MULOP, MULOP,	// 5行目
						// 6行目
    ID, ADDOP, ID, ID,				// 7行目
    ID, 					// 8行目
    ADDOP, MULOP, MULOP,			// 9行目
    ADDOP,					// 10行目
    ID, LOGOP, 					// 11行目
    LOGOP, LOGOP, ADDOP, ID, LOGOP, 		// 12行目
    LOGOP, MULOP, LOGOP, MULOP, LOGOP,		// 13行目
						// 14行目
						// 15行目
    ID, EOF };					// 16行目

// 識別子の字句
const char *ids[] = {
  "var1", "cat", "varcomm", "function", "ab", 	// 1行目
  "cD5a10qg2ZwQ", "funcvar", "whileif", 	// 2行目
  "if2q", "elsifw",				// 4行目
  "A2q", 					// 5行目
  "q1if", "k23", "ret", 			// 7行目
  "urn",					// 8行目
  "aA23509", 					// 11行目
  "B",						// 12行目
  "a" };					// 16行目

// 演算子の種別(const.hを参照)
int ops[] = {
  Cadd, Csubtract, Cmultiply, Cmodulo, 		// 2行目
  Cdivide, 					// 4行目
  Cadd, Cadd, Cadd, Cdivide, Cmultiply,		// 5行目
  Cadd,						// 7行目
  Csubtract, Cdivide, Cmodulo,			// 9行目
  Cadd,						// 10行目
  Cand,						// 11行目
  Cor, Cand, Cadd, Cand,			// 12行目
  Cand,  Cdivide, Cor, Cmultiply, Cor };	// 13行目

int inums[] = { };

double rnums[] = { };
