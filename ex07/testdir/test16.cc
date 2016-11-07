/************************************************************************
  テスト１６： findVariable() の異常ケースのテスト１
  (1) addGlobalVariable(), addLocalVariable(), addParameter(), 
      addArray() を使って、globalSymTable と localSymTable に
      変数エントリを登録する。
  (2) 登録されていない変数エントリの識別子名を指定して、findVariable()
      を呼び出したときにエラーになることを確かめる。

**********************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "../symtable.h"
#include "../error.h"
#include "../const.h"
#include "symtable-test.h"


static void printResult(string name, SymbolEntry *symbol);

char filename[] = "dummy";

main()
{
  VarEntry *var;
  string varname0 = string("aVariable0");
  string varname1 = string("aVariable1");
  string varname2 = string("aVariable2");
  string varname3 = string("aVariable3");
  string varname4 = string("aVariable4");
  string varname5 = string("aVariable5");

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  addLocalVariable(varname1,TInt);
  addGlobalVariable(varname2,TInt);
  addParameter(varname3,TReal);
  addArray(varname4,TInt,10);
  addLocalVariable(varname5,TReal);

  printResult(varname3, findVariable(varname3));
  printResult(varname5, findVariable(varname5));
  printResult(varname1, findVariable(varname1));
  printResult(varname3, findVariable(varname3));
  printResult(varname5, findVariable(varname5));
  printResult(varname4, findVariable(varname4));
  printResult(varname2, findVariable(varname2));
  printResult(varname1, findVariable(varname1));
  // ここでエラーが発生する
  printResult(varname0, findVariable(varname0));	// 見つからない
}


static void printResult(string name, SymbolEntry *symbol)
{
  printf("変数%sが見つかりました\n",name.c_str());
}
