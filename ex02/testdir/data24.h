/**************************************************
 テストデータ２４
   実数を読んでいるときに E の後に符号、数字
   以外の文字を読んだらエラー

**************************************************/

#define NumOfTokens	(sizeof(tokens)/sizeof(int))


unsigned char buffer[] = "\n\
 \t1.5E*5";


int tokens[] = 
  { RNUM }; /* 最後の RNUM はダミー */

const char *ids[] = { }; 

int inums[] = { };

double rnums[] = { 1.5E5 };

int ops[] = { };

