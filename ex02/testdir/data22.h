/**************************************************
 テストデータ２２
   不正な文字 _ を読んだらエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \t_ab";


int tokens[] = 
  { ID }; /* 最後の ID はダミー */

const char *ids[] = { "_ab" }; 

int inums[] = { };

double rnums[] = { };

int ops[] = { };

