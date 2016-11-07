/****************************************************************************
  テスト１１： addLocalVariable() の異常ケースのテスト
  (1) addLocalVariable() などを呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 局所変数と同名の局所変数を登録したときエラーになることを確かめる．

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "error.h"
#include "symtable.h"
#include "const.h"
#include "symtable-test.h"

// symtable-test.cc で定義
void printAllSymbols(void);

char filename[] = "dummy";


main()
{
  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  addLocalVariable("aVariable1",TInt);
  addGlobalVariable("aVariable2",TReal);
  addParameter("aVariable3",TReal);
  addGlobalVariable("aVariable4",TReal);
  // ここでエラーが発生する
  addLocalVariable("aVariable1",TReal);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

