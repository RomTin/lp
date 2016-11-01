/********************************************************
*  lf-scanner.h: lf-scanner.cc のインタフェース・ファイル  *
*                                                       *
********************************************************/

#ifndef __LFSCANNER_H__
#define __LFSCANNER_H__

// 字句解析系のための関数のプロトタイプ宣言
int getToken(void);			// 字句解析系の本体
void initializeScanner(char *name);	// 字句解析系の初期化
const char *getLexeme(int token);	// トークンの字句(lexeme)の取得

#endif
