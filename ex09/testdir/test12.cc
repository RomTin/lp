/****************************************************************************
  テスト１２： defineProcedure() の異常ケースのテスト３
  (1) addProcedured() を呼び出して globalSymTable に手続きエントリを登録する。
  (2) defineProcedure() を呼び出して、手続きを定義する。
  (3) 既に定義された手続きを defineProcedure() で再定義して、
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
  ParamList *params2 = new ParamList;

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  params1->push_back(ParamType(TReal,string("var")));
  addProcedure(name1,TVoid,params1);

  params2->push_back(ParamType(TReal,string("v")));
  params2->push_back(ParamType(TReal,string("x")));
  params2->push_back(ParamType(TInt,string("y")));
  params2->push_back(ParamType(TInt,string("z")));
  addProcedure(name2,TReal,params2);

  addProcedure(name3,TInt,NULL);

  defineProcedure(name1,TVoid);
  defineProcedure(name3,TInt);
  defineProcedure(name1,TVoid);	// 定義済なのでエラー

  printAllSymbols();
}

