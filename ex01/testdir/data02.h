/**************************************************
 テストデータ２
   scanner.c についての正常ケースのテスト
   (コメントがEOFで終わる場合)

**************************************************/


#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列 (\n が改行)
unsigned char buffer[] = "  var1 ///end-of-file";


// トークン
int tokens[] = 
  { ID, EOF };		// 1行目

// 識別子の字句
const char *ids[] = { "var1" };

// 演算子の種別
int ops[] = { };
