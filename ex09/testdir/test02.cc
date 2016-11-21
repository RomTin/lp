/****************************************************************************
  テスト２： addProcedure() の正常ケースのテスト２
  (1) addLocalVariable(), addParameter() を呼び出して
      localSymTable に変数エントリを登録する。
  (2) addProcedure() を呼び出して、局所変数や仮引数と同名の関数を
      登録してもエラーにならないことを確かめる。
  (3) 最後に、それぞれの記号表に変数エントリが登録されているかどうか、
      各記号表の内容をすべて表示する。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "symtable-test.h"

int lineNo;

main()
{
  ParamList *params = new ParamList;
  params->push_back(make_pair(TInt,string("zzz")));

  string name1 = string("xxx");
  string name2 = string("yyy");
  addLocalVariable(name1,TInt);
  addParameter(name2,TReal);
  addProcedure(name1,TInt,NULL);
  addProcedure(name2,TVoid,params);

  printAllSymbols();
}

