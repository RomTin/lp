/****************************************************************************
  テスト２１： checkParamList() の正常ケーステスト
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
  (2) checkParamList() を正しい引数リストで呼び出して、
      エラーにならないことを確かめる。
  (3) checkParamList() を実際より多い引数個数で呼び出して、
      エラーになることを確かめる。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "symtable-test.h"

int lineNo;


main()
{
  ParamList *params1 = new ParamList;
  ParamList *params2 = new ParamList;
  ParamList *params3 = new ParamList;

  // 記号表への手続きの登録
  params1->push_back(ParamType(TReal,string("v")));
  params1->push_back(ParamType(TReal,string("x")));
  params1->push_back(ParamType(TInt,string("y")));
  params1->push_back(ParamType(TInt,string("z")));
  ProcEntry *proc1 = addProcedure(string("aCommand"),TVoid,params1);

  params2->push_back(ParamType(TReal,string("abort")));
  ProcEntry *proc2 = addProcedure(string("aFunction"),TInt,params2);

  params3->push_back(ParamType(TInt,string("graph")));
  params3->push_back(ParamType(TReal,string("program")));
  params3->push_back(ParamType(TInt,string("edge")));
  ProcEntry *proc3 = addProcedure(string("kind"),TInt,params3);

  ProcEntry *proc4 = addProcedure(string("camera"),TReal,NULL);

  ParamList *dparams1 = new ParamList;
  ParamList *dparams2 = new ParamList;
  ParamList *dparams3 = new ParamList;

  // 引数個数のチェック（正常ケース）
  dparams2->push_back(ParamType(TReal,string("abort")));
  checkParamList(dparams2,proc2);

  dparams1->push_back(ParamType(TReal,string("v")));
  dparams1->push_back(ParamType(TReal,string("x")));
  dparams1->push_back(ParamType(TInt,string("y")));
  dparams1->push_back(ParamType(TInt,string("z")));
  checkParamList(dparams1,proc1);

  // 引数がない場合
  checkParamList(NULL,proc4);

  // 名前は違うが型は同じ
  dparams3->push_back(ParamType(TInt,string("i")));
  dparams3->push_back(ParamType(TReal,string("j")));
  dparams3->push_back(ParamType(TInt,string("k")));
  checkParamList(dparams3,proc3);

  printf("正常終了\n");
}

