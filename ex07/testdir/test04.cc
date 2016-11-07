/************************************************************************
  テスト４： addVariable() の異常ケースのテスト２
  (1) 自分で記号表を用意する．
  (2) その記号表に，記号表エントリの種別が SymProc である記号表
      エントリを登録する．
  (3) addVariable() にその記号表を渡して，同名の変数をもつ
      変数エントリを登録して，エラーになることを確かめる．

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
  // 識別子名 "aVariable2" をもち，記号表エントリの種別が SymProc の
  // 記号表エントリを myTable に登録する．
  myTable.insert(make_pair(string("aVariable2"),
                           new SymbolEntry(SymProc,"aVariable2",TInt)));
  addVariableG("aVariable3",Param,TReal,false,0,&myTable);
  // ここでエラーが発生する
  addVariableG("aVariable2",GlobalVar,TReal,true,10,&myTable);

  // この後には到達しない。到達して変数エントリの情報が
  // 出力されたらエラーが発生していないので誤り
  SymbolTable::iterator it, ie = myTable.end();

  for (it=myTable.begin(); it != ie; it++)
    // 変数エントリへのポインタを，symtable-test.cc で定義した
    // printSymbol()に渡し，変数エントリの情報を出力する．
    printSymbol(it->second);
}

