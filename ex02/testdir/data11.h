/**************************************************
 テストデータ１１
   不正な文字 " を読んだらエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \"a";


int tokens[] = 
  { ';' }; /* 最後の ';' はダミー */

const char *ids[] = { }; 

int inums[] = { };

double rnums[] = { };

int ops[] = { };

