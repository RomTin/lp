/*******************************************************
*  scanner.h: scanner.cc のインタフェース・ファイル    *
*                                                      *
*******************************************************/

// scanner.cc で定義されている関数のプロトタイプ宣言

#ifndef __TGLC_SCANNER_H__
#define __TGLC_SCANNER_H__

void initializeScanner(char *filename);
int yylex(void);

#endif
