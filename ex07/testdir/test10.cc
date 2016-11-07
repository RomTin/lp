/****************************************************************************
  テスト１０： addArray() の異常ケースのテスト
  (1) addAdday() などを呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 配列と同名の配列を登録したときエラーになることを確かめる．

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
  addArray("aVariable3",TInt,5);
  addParameter("aVariable4",TInt);
  addGlobalVariable("aVariable5",TReal);
  // ここでエラーが発生する
  addArray("aVariable3",TReal,10);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

