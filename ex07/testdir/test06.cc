/****************************************************************************
  テスト６： addGlobalVariable(), addLocalVariable(), 
             addParameter(), addArray() の正常ケースのテスト２
  (1) addGlobalVariable(), addLocalVariable(), addParameter(),
      addArray() を呼び出して、globalSymTable や localSymTable に
      globalSymTable や localSymTable に変数エントリを登録する。
  (2) 大域変数と同名の局所変数、仮引数を登録してもエラーにならない
      ことを確かめる。
  (3) 最後に、それぞれの記号表に，変数エントリが登録されているかどうか、
      各記号表の内容をすべて表示する。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "const.h"
#include "symtable-test.h"


main()
{
  addLocalVariable("aVariable1",TInt);
  addGlobalVariable("aVariable2",TReal);
  addArray("aVariable3",TInt,10);
  addParameter("aVariable3",TInt);
  addGlobalVariable("aVariable4",TInt);
  addArray("aVariable5",TReal,10);
  addLocalVariable("aVariable2",TReal);
  addParameter("aVariable4",TInt);
  addLocalVariable("aVariable5",TReal);

  printAllSymbols();
}

