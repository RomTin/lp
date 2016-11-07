/************************************************************************
  テスト３： addVariable() の異常ケースのテスト１
  (1) 自分で記号表を用意する．
  (2) addVariable() にその記号表を渡して，変数エントリを登録する．
  (3) 同じ名前をもつ変数を登録して，エラーになるかどうかテストする．

**********************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "error.h"
#include "const.h"
#include "symtable-test.h"


char filename[] = "dummy";

main()
{
  SymbolTable myTable;

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  addVariableG("aVariable1",LocalVar,TInt,false,0,&myTable);
  addVariableG("aVariable2",GlobalVar,TInt,true,10,&myTable);
  addVariableG("aVariable3",Param,TReal,false,0,&myTable);
  addVariableG("aVariable4",GlobalVar,TReal,false,0,&myTable);
  // ここでエラーが発生する
  addVariableG("aVariable2",LocalVar,TReal,false,0,&myTable);

  // この後には到達しない。到達して変数エントリの情報が
  // 出力されたらエラーが発生していないので誤り
  SymbolTable::iterator it, ie = myTable.end();

  for (it=myTable.begin(); it != ie; it++)
    // 変数エントリへのポインタを，symtable-test.cc で定義した
    // printSymbol()に渡し，変数エントリの情報を出力する．
    printSymbol(it->second);
}

