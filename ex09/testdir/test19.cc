/****************************************************************************
  テスト１９： findProcedure() の異常ケースのテスト１
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
  (1) defineProcedure() を呼び出して手続きを定義する。
  (3) 記号表にない名前を指定して findProcedure() を呼び出すと
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
  ParamList *params1 = new ParamList;
  ParamList *params2 = new ParamList;
  ParamList *params3 = new ParamList;

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  // 記号表への手続きの登録
  params1->push_back(ParamType(TReal,string("v")));
  params1->push_back(ParamType(TInt,string("x")));
  addProcedure(string("aCommand"),TVoid,params1);

  params2->push_back(ParamType(TReal,string("a")));
  params2->push_back(ParamType(TInt,string("b")));
  params2->push_back(ParamType(TInt,string("c")));
  addProcedure(string("aFunction"),TReal,params2);

  addLocalVariable(string("noName"),TInt);

  params3->push_back(ParamType(TInt,string("b")));
  addProcedure(string("kind"),TInt,params3);

  // 手続きの定義
  defineProcedure(string("aFunction"),TReal);
  defineProcedure(string("aCommand"),TVoid);
  defineProcedure(string("kind"),TInt);

  // 手続きの検索
  printSymbol(findProcedure(string("noName")));	// 記号表にない名前なのでエラー

  // globalSymTable に保存されたすべての記号表エントリを出力する．
  printAllGlobalSymbols();
}

