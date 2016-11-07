/****************************************************************************
  テスト１２： addLocalVariable(), addParameter() の異常ケースのテスト
  (1) addLocalVariable(), addParameter() などを呼び出して
      globalSymTable や localSymTable に変数エントリを登録する．
  (2) 局所変数と同名の仮引数を登録したときエラーになることを確かめる．

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

  addLocalVariable("aVariable1",TReal);
  addGlobalVariable("aVariable2",TInt);
  addParameter("aVariable3",TInt);
  addGlobalVariable("aVariable4",TInt);
  // ここでエラーが発生する
  addParameter("aVariable1",TInt);

  // ここには到達してはならないので、変数の情報が出力されたら誤り
  printAllSymbols();
}

