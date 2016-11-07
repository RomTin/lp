/****************************************************************************
  テスト１４： addParameter() の異常ケースのテスト
  (1) addParameter() などを呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 仮引数と同名の仮引数を登録したときエラーになることを確かめる．

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
  addGlobalVariable("aVariable2",TReal);
  addParameter("aVariable3",TReal);
  addGlobalVariable("aVariable4",TInt);
  // ここでエラーが発生する
  addParameter("aVariable3",TInt);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

