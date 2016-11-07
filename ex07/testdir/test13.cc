/****************************************************************************
  テスト１３： addLocalVariable(), addParameter() の異常ケースのテスト２
  (1) addGlobalVariable(), addLocalVariable(), addParameter() を呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 仮引数と同名の局所変数を登録したときエラーになることを確かめる．

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

  addLocalVariable("aVariable1",TInt);
  addGlobalVariable("aVariable2",TReal);
  addParameter("aVariable3",TInt);
  addGlobalVariable("aVariable4",TReal);
  // ここでエラーが発生する
  addLocalVariable("aVariable3",TInt);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

