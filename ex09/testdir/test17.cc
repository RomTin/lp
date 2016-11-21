/****************************************************************************
  テスト１７： defineProcedure() の異常ケースのテスト５
  (1) addGlobalVariable, addProcedure() を呼び出して、
      globalSymTable に変数エントリ，手続きエントリを登録する。
  (2) 登録された大域変数と同名の手続きを定義するとエラーになることを確かめる。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "error.h"
#include "symtable.h"
#include "symtable-test.h"

int lineNo;
char filename[] = "dummy";


main()
{
  string name1 = string("acrobat");
  string name2 = string("circus");
  string name3 = string("chamber");
  ParamList *params1 = new ParamList;
  ParamList *params3 = new ParamList;

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  params1->push_back(ParamType(TInt,string("var")));
  addProcedure(name1,TInt,params1);

  addGlobalVariable(name2,TInt);

  params3->push_back(ParamType(TInt,string("var2")));
  addProcedure(name3,TInt,params3);

  defineProcedure(name2,TInt);	// 大域変数として宣言されているのでエラー

  printAllSymbols();
}

