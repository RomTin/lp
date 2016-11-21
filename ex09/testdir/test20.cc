/****************************************************************************
  テスト２０： findProcedure() の異常ケースのテスト２
  (1) addGlobalVariable, addProcedure() を呼び出して、
      globalSymTable に変数エントリと手続きエントリを登録する。
  (2) defineProcedure() を呼び出して、手続きを定義する。
  (3) 大域変数と同じ名前を指定して findProcedure() を呼び出すと、
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
  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  // 記号表への手続きの登録
  addProcedure(string("aCommand"),TInt,NULL);
  addProcedure(string("aFunction"),TInt,NULL);
  addProcedure(string("kind"),TInt,NULL);
  // 記号表への大域変数の登録
  addGlobalVariable(string("noName"),TInt);

  // 手続きの定義
  defineProcedure(string("aFunction"),TInt);
  defineProcedure(string("aCommand"),TInt);
  defineProcedure(string("kind"),TInt);

  // 手続きの検索
  printSymbol(findProcedure(string("noName")));	// 大域変数と同じ名前なのでエラー

  // globalSymTable に保存されたすべての記号表エントリを出力する．
  printAllGlobalSymbols();
}

