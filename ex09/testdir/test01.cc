/****************************************************************************
  テスト１： addProcedure() の正常ケースのテスト１
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
      返り値を printSymbol() に渡し，手続きエントリの内容を表示する。
  (2) globalSymTable にすべての手続きエントリが登録されているかどうか、
      globalSymTable の内容をすべて表示する。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "symtable-test.h"

int lineNo;

main()
{
  // 記号表への登録をテストする．
  ParamList *params1, *params2, *params3, *params4;

  params1 = new ParamList;
  params1->push_back(ParamType(TInt,string("aVar1")));
  params1->push_back(ParamType(TReal,string("aVar2")));
  params1->push_back(ParamType(TInt,string("aVar3")));
  printSymbol(addProcedure(string("aCommand"),TVoid,params1));

  params2 = NULL;
  printSymbol(addProcedure(string("aFunction"),TInt,params2));

  params3 = new ParamList;
  params3->push_back(ParamType(TReal,string("aVar25")));
  params3->push_back(ParamType(TReal,string("aVar30")));
  printSymbol(addProcedure(string("computer"),TVoid,params3));

  params4 = new ParamList;
  params4->push_back(ParamType(TInt,string("aVar60")));
  params4->push_back(ParamType(TInt,string("aVar92")));
  printSymbol(addProcedure(string("another"),TReal,params4));
  
  // globalSymTable に保存されたすべての記号表エントリを出力する．
  printAllGlobalSymbols();

  delete params1;
  delete params2;
  delete params3;
  delete params4;
}

