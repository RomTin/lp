/****************************************************************************
  テスト５： addGlobalVariable(), addLocalVariable(), 
             addParameter(), addArray() の正常ケースのテスト１
  (1) addGlobalVariable(), addLocalVariable(), addParameter(),
      addArray() を呼び出して、globalSymTable や localSymTable に
      変数エントリを登録する。
  (2) それぞれの記号表に変数エントリが登録されているかどうか、
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
  // 記号表への登録をテストする．
  addLocalVariable("aVariable1",TInt);
  addGlobalVariable("aVariable2",TInt);
  addParameter("aVariable3",TInt);
  addGlobalVariable("aVariable4",TReal);
  addParameter("aVariable5",TReal);
  addLocalVariable("aVariable6",TReal);
  addArray("aVariable7",TReal,5);
  addArray("aVariable8",TInt,20);

  // globalSymTable と localSymTable に保存された
  // すべての変数エントリを出力する．
  printAllSymbols();
}

