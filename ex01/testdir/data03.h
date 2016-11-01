/**************************************************
 テストデータ３
   getCharacterで行番号を正しく更新しているか
   (エラーが発生する行が１行目のとき）

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))

// 入力文字列
unsigned char buffer[] = " abc$$";


// トークン
int tokens[] = { ID, ID };	// 最後の ID はダミー

// 識別子の字句
const char *ids[] = { "abc", "a" }; // 最後の"a"はダミー

// 演算子の種別
int ops[] = { };

