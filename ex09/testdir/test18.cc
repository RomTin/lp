/****************************************************************************
  テスト１８： findProcedure() の正常ケースのテスト
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
  (2) defineProcedure() を呼び出して手続きを定義する。
  (3) addLocalVariable(), addParameter() を呼び出して手続きと同名の局所変数と
      仮引数の変数エントリを localSymTable に登録する。
  (4) findProcedure() を呼び出して、得られた手続きエントリの情報を出力する。

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
  params1->push_back(ParamType(TReal,string("a")));
  params1->push_back(ParamType(TInt,string("b")));
  params1->push_back(ParamType(TInt,string("c")));
  params1->push_back(ParamType(TInt,string("d")));
  addProcedure(string("aCommand"),TVoid,params1);

  params2->push_back(ParamType(TInt,string("b")));
  params2->push_back(ParamType(TInt,string("a")));
  params2->push_back(ParamType(TInt,string("c")));
  addProcedure(string("aFunction"),TInt,params2);

  params3->push_back(ParamType(TReal,string("var1")));
  params3->push_back(ParamType(TInt,string("var2")));
  addProcedure(string("computer"),TReal,params3);

  // 手続きの定義
  defineProcedure(string("computer"),TReal);
  defineProcedure(string("aFunction"),TInt);
  defineProcedure(string("aCommand"),TVoid);

  // 手続きと同名の局所変数と仮引数の登録
  addLocalVariable(string("aCommand"),TReal);
  addLocalVariable(string("aFunction"),TInt);
  addParameter(string("computer"),TReal);

  // 手続きの検索
  printSymbol(findProcedure(string("aCommand")));
  printSymbol(findProcedure(string("aFunction")));
  printSymbol(findProcedure(string("aCommand")));
  printSymbol(findProcedure(string("computer")));

  // globalSymTable に保存されたすべての記号表エントリを出力する
  printAllGlobalSymbols();
}

