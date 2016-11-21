/****************************************************************************
  テスト９： defineProcedure() の異常ケースのテスト２
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
  (2) addProcedure() で登録された手続きと名前が同じで返り値の型が異なる手続きを
      defineProcedure() で定義して、エラーになることを確かめる。

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

  params1->push_back(make_pair(TReal,string("var1")));
  params1->push_back(make_pair(TInt,string("var2")));
  params1->push_back(make_pair(TInt,string("var3")));
  addProcedure(name1,TInt,params1);

  addProcedure(name2,TReal,NULL);
  params3->push_back(ParamType(TInt,string("var31")));
  params3->push_back(ParamType(TInt,string("var32")));
  addProcedure(name3,TVoid,params3);

  defineProcedure(name1,TReal);	// 実数型でなく整数型として宣言されているのでエラー

  printAllSymbols();
}

