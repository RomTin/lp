/*******************************************************
*  scanner.h: scanner.cc のインタフェース・ファイル    *
*                                                      *
*******************************************************/

// scanner.cc で定義されている関数のプロトタイプ宣言

#ifndef __SCANNER_H__
#define __SCANNER_H__

void initializeScanner(char *filename);
int yylex(void);

#endif
