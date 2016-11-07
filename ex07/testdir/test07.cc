/****************************************************************************
  テスト７： addGlobalVariable(), addArray() の異常ケースのテスト１
  (1) addGlobalVariable(), addArray() などを呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 大域変数と同名の配列を登録したときエラーになることを確かめる．

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
  addArray("aVariable2",TReal,30);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

