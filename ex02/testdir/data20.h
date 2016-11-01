/**************************************************
 テストデータ２０
   不正な文字 . を読んだらエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \t.25\"a";


int tokens[] = 
  { RNUM }; /* 最後の RNUM はダミー */

const char *ids[] = { }; 

int inums[] = { };

double rnums[] = { 0.25 };

int ops[] = { };

