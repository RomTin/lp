/********************************************************
*  interpret.h: interpret.cc のインタフェース・ファイル *
*                                                       *
********************************************************/

// interpret.cc で定義されている関数のプロトタイプ宣言

#ifndef __TGLC_INTERPRET_H__
#define __TGLC_INTERPRET_H__

#include "const.h"
#include "symtable.h"
#include "code.h"


// 名前 nameをもつ int 型の変数の初期値 val をメモリに割り当てる
// 返り値は，変数に割り当てられたメモリの番地
int allocateMemory(int val);

// 名前 name をもつ real 型の変数の初期値 val をメモリに割り当てる
// 返り値は，変数に割り当てられたメモリの番地
int allocateMemory(double val);

// 変数をインタプリタに登録する
void registerVariable(VarEntry *var);

// code が指す命令列を解釈実行する
void interpret(Code *code);

// システム定義手続きを追加する
void addSystemProcedures(void);

// インタプリタの実行速度を設定する
void setSpeed(int speed);

// 中間コードを出力する
void printCode(Code *code);

// トレースモードにする。
// トレースモードになるとインタプリタは中間コードのトレース実行を行う
void setTrace();

#endif
