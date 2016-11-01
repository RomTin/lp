/**************************************************
 課題１ テストデータ５
  ＆ を一つだけしか読まなければエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \txyz&|";


int tokens[] = 
  { ID, LOGOP };	// 最後の LOGOP はダミー

const char *ids[] = { "xyz" }; 

int ops[] = { Cand };	// 最後の Cand はダミー


int inums[] = { };

double rnums[] = { };
