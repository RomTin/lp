/****************************************************************************
  テスト９： addGlobalVariable() の異常ケースのテスト
  (1) addGlobalVariable() などを呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 大域変数と同名の大域変数を登録したときエラーになることを確かめる．

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "error.h"
#include "symtable.h"
#include "const.h"
#include "symtable-test.h"

char filename[] = "dummy";


main()
{
  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  addLocalVariable("aVariable1",TReal);
  addGlobalVariable("aVariable2",TInt);
  addParameter("aVariable3",TInt);
  addGlobalVariable("aVariable4",TReal);
  // ここでエラーが発生する
  addGlobalVariable("aVariable2",TReal);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

