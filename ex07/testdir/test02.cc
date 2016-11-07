/************************************************************************
  テスト２： addVariable(), の正常ケースのテスト１
             getName(), getType(), isArray(), getArraySize(),
             isGlobalVariable(), isLocalVariable(), isParameter(),
             isVariable(), isProcedure() もテスト
  (1) 自分で記号表を用意する。
  (2) addVariable() にその記号表を渡して，変数エントリを登録する。
      addVariable() の返り値は保存しておく。
  (3) 変数エントリが記号表にちゃんと登録されているかどうか、
      記号表の内容をすべて表示する．ここで呼び出される関数printSymbol()
      の中で getName(), getType(), isArray(), getArraySize(),
      isGlobalVariable(), isLocalVariable(), isParameter(),
      isVariable(), isProcedure() を呼び出すので，
      これらの関数もここでテストされる。

**********************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "const.h"
#include "symtable-test.h"

static void compareResult(VarEntry *var, string name, SymbolTable *table);

main()
{
  SymbolTable myTable;
  VarEntry *var1, *var2, *var3, *var4, *var5;

  // 内部でaddVariable() を呼び出す関数 addVariableG() （symtable-test.cc
  // で定義）を呼び出し，addVariable() のテストを行う．
  var1 = addVariableG("aVariable1",LocalVar,TInt,false,0,&myTable);
  var2 = addVariableG("aVariable2",GlobalVar,TReal,false,0,&myTable);
  var3 = addVariableG("aVariable3",Param,TInt,false,0,&myTable);
  var4 = addVariableG("aVariable4",GlobalVar,TInt,true,20,&myTable);
  var5 = addVariableG("aVariable5",LocalVar,TReal,false,0,&myTable);
  // isVariable() と isProcedure() もテストするために，
  // ここで記号表エントリの種別として SymProc をもつ
  // 記号表エントリを直接作って，myTableに登録しておく．
  SymbolEntry *symbol = new SymbolEntry(SymProc,"aProcedure",TInt);
  myTable.insert(make_pair(string("aProcedure"),symbol));

  // myTable に登録したすべての変数エントリを順に表示する．
  SymbolTable::iterator it, ie = myTable.end();

  for (it=myTable.begin(); it != ie; it++)
    // 変数エントリへのポインタを，symtable-test.cc で定義した
    // printSymbol()に渡し，変数エントリの情報を出力する．
    printSymbol(it->second);
}
