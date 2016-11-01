/**************************************************
 テストデータ８
   一つ目の’の後がEOFならばエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \t'a''";



int tokens[] = { INUM, INUM };	// 最後の INUM はダミー

const char *ids[] = { }; 

int inums[] = { 'a', 'a' };	// 最後の'a'はダミー

double rnums[] = { };

int ops[] = { };

