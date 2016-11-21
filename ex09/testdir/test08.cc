/****************************************************************************
  テスト８： defineProcedure() の異常ケースのテスト１
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
  (2) 登録されていない手続きを defineProcedure() で定義して、
      エラーになることを確かめる。

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

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  params1->push_back(ParamType(TReal,string("var1")));
  params1->push_back(ParamType(TInt,string("var2")));
  params1->push_back(ParamType(TInt,string("var3")));
  addProcedure(name1,TInt,params1);

  addLocalVariable(name2,TInt);

  addProcedure(name3,TVoid,NULL);

  defineProcedure(name2,TInt);	// globalSymTable にない名前なのでエラー

  printAllSymbols();
}

