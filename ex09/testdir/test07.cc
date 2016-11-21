/****************************************************************************
  テスト７： defineProcedure(), addLocalVariable(), addParameter() のテスト
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
  (2) defineProcedure() を呼び出して手続きを定義する。
  (3) addLocalVariable(), addParameter() を呼び出して、局所変数と仮引数を
      localSymTable に登録する。
  (4) 局所変数と仮引数の位置が正しくセットされていることを確かめるために、
      記号表の内容をすべて表示する。
  (5) 再び手続きを定義してから、(3)(4)を繰り返し，localSymTable が
      手続きの定義によりクリアされていることを確かめる。

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
  string name3 = string("compiler");
  ParamList *params1 = new ParamList;
  ParamList *params2 = new ParamList;
  ParamList *params3 = new ParamList;

  params1->push_back(ParamType(TReal,string("var1")));
  params1->push_back(make_pair(TInt,string("var2")));
  params1->push_back(ParamType(TInt,string("var3")));
  addProcedure(name1,TInt,params1);

  params2->push_back(ParamType(TInt,string("var21")));
  params2->push_back(make_pair(TReal,string("var22")));
  params2->push_back(make_pair(TInt,string("var23")));
  params2->push_back(make_pair(TReal,string("var24")));
  addProcedure(name2,TVoid,params2);

  params3->push_back(ParamType(TReal,string("var31")));
  params3->push_back(ParamType(TReal,string("var32")));
  addProcedure(name3,TReal,params3);

  // 手続きの定義
  defineProcedure(name1,TInt);
  // 仮引数と局所変数の登録
  addParameter("aParam1",TReal);
  addParameter("aParam2",TInt);
  addParameter("aParam3",TInt);
  addLocalVariable("aLocalVar1",TInt);
  addLocalVariable("aLocalVar2",TInt);
  addLocalVariable("aLocalVar3",TReal);
  addLocalVariable("aLocalVar4",TReal);
  // 記号表の内容を出力
  printAllSymbols();

  // 手続きの定義
  defineProcedure(name2,TVoid);
  // 仮引数と局所変数の登録
  addParameter("aParam1",TInt);
  addParameter("aParam2",TReal);
  addParameter("aParam3",TInt);
  addParameter("aParam4",TReal);
  addLocalVariable("aLocalVar1",TReal);
  addLocalVariable("aLocalVar2",TReal);
  addLocalVariable("aLocalVar3",TInt);
  addLocalVariable("aLocalVar4",TReal);
  addLocalVariable("aLocalVar5",TInt);
  addLocalVariable("aLocalVar6",TInt);
  addLocalVariable("aLocalVar7",TReal);
  // 記号表の内容を出力
  printAllSymbols();

  // 手続きの定義
  defineProcedure(name3,TReal);
  // 仮引数と局所変数の登録
  addParameter("aParam4",TReal);
  addParameter("aParam2",TReal);
  addLocalVariable("aLocalVar8",TReal);
  addLocalVariable("aLocalVar1",TReal);
  addLocalVariable("aLocalVar9",TInt);
  addLocalVariable("aLocalVar5",TInt);
  addLocalVariable("aLocalVar7",TInt);
  addLocalVariable("aLocalVar3",TInt);
  addLocalVariable("aLocalVar4",TInt);
  addLocalVariable("aLocalVar6",TReal);
  addLocalVariable("aLocalVar2",TInt);
  // 記号表の内容を出力
  printAllSymbols();
}




