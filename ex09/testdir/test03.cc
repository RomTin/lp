/****************************************************************************
  テスト３： addProcedure() の異常ケースのテスト１
  (1) addGlobalVariable() を呼び出して大域変数を登録する。
  (2) addProcedure() を呼び出して、大域変数と同名の手続きの
      手続きエントリを globalSymTable に登録する。
  (3) 大域変数と同名の手続きを登録したときエラーになることを確かめる。

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
  string name = string("sameName");

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  addGlobalVariable(name,TInt);
  addProcedure(name,TVoid,NULL); // 同名の大域変数が宣言済なのでエラー

  printAllSymbols();
}

