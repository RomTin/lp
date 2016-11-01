/*******************************************************
*  scanner.h: scanner.cc のインタフェース・ファイル    *
*                                                      *
*******************************************************/

// scanner.cc で定義されている関数のプロトタイプ宣言

void initializeScanner(char *filename);
int yylex(void);
