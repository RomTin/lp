/**************************************************
 テストデータ２６
   実数を読んでいるときに - の後に数字以外の
   文字を読んだらエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \t 1.5E--5";


int tokens[] = 
  { RNUM }; /* 最後の RNUM はダミー */

const char *ids[] = { }; 

int inums[] = { };

double rnums[] = { 1.5e-5 };

int ops[] = { };

