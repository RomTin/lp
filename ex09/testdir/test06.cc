/****************************************************************************
  テスト６： defineProcedure() の正常ケースのテスト１
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
      返り値は変数に保存しておく．
  (2) addProcedure() で登録した手続きを defineprocedure() で定義する．
      返り値を printSymbol() に渡し，手続きエントリの内容を表示する．
      また，返り値が addProcedure() が返した値と同じかどうかチェックする．
  (3) globalSymTable に手続きエントリが登録されているかどうか，
      globalSymTable の内容をすべて表示する．

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "symtable-test.h"

int lineNo;

main()
{
  string name1 = string("acrobat");
  string name2 = string("circus");
  ParamList *params = new ParamList;

  params->push_back(make_pair(TInt,string("var1")));
  params->push_back(make_pair(TReal,string("var2")));
  ProcEntry *procDeclared = addProcedure(name1,TInt,params);
  addProcedure(name2,TInt,params);

  ProcEntry *procDefined = defineProcedure(name1,TInt);
  printf("addProcedure()とdefineProcedure()の返り値は");
  if (procDeclared == procDefined)
    printf("同一\n");
  else
    printf("異なる\n");
  printSymbol(procDefined);

  printAllGlobalSymbols();
}

