/**************************************************
 テストデータ１０
   一つ目の’の２文字後が’でなければエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \t 'ab'de";



int tokens[] = { INUM };	// 最後の INUM はダミー

const char *ids[] = { }; 

int inums[] = { 'a' };		// 'a'はダミー

double rnums[] = { };

int ops[] = { };

