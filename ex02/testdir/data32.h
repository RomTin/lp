/**************************************************
 課題１ テストデータ６
  ｜ を一つだけしか読まなければエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \txyz|&";


int tokens[] = 
  { ID, LOGOP };	// 最後の LOGOP はダミー

const char *ids[] = { "xyz" }; 

int ops[] = { Cor };	// 最後の Cor はダミー


int inums[] = { };

double rnums[] = { };
