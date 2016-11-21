/****************************************************************************
  テスト２８： checkParamList() の異常ケースのテスト７
  (1) addProcedure() を呼び出して、globalSymTable に引数をもつ手続きの
      エントリを登録する。
  (3) checkParamList() に、引数個数は同じだが最後の引数の型が違う引数リストを
      渡して呼び出して、エラーになることを確かめる。

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
  ParamList *params1 = new ParamList;
  ParamList *params2 = new ParamList;

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  // 記号表への手続きの登録
  params1->push_back(ParamType(TReal,string("v")));
  params1->push_back(ParamType(TReal,string("x")));
  params1->push_back(ParamType(TInt,string("y")));
  ProcEntry *proc1 = addProcedure(string("aCommand"),TVoid,params1);

  params2->push_back(ParamType(TReal,string("a")));
  params2->push_back(ParamType(TReal,string("b")));
  params2->push_back(ParamType(TInt,string("c")));
  params2->push_back(ParamType(TInt,string("d")));
  params2->push_back(ParamType(TInt,string("e")));
  ProcEntry *proc2 = addProcedure(string("aFunction"),TInt,params2);

  ParamList *dparams1 = new ParamList;
  ParamList *dparams2 = new ParamList;

  // 引数個数のチェック（正常ケース）
  dparams1->push_back(ParamType(TReal,string("v")));
  dparams1->push_back(ParamType(TReal,string("x")));
  dparams1->push_back(ParamType(TInt,string("y")));
  checkParamList(dparams1,proc1);

  // 引数個数のチェック（異常ケース: 最後の引数の型が違う）
  dparams2->push_back(ParamType(TReal,string("a")));
  dparams2->push_back(ParamType(TReal,string("b")));
  dparams2->push_back(ParamType(TInt,string("c")));
  dparams2->push_back(ParamType(TInt,string("d")));
  dparams2->push_back(ParamType(TReal,string("e")));
  checkParamList(dparams2,proc2);
}

