/****************************************************************************
  テスト４： addprocedure() の異常ケースのテスト２
  (1) addProcedure() を２回呼び出して、同じ名前の手続きのエントリを
      globalSymTable に登録する。
  (2) 以前に登録した手続きと同名の手続きを登録したとき
      エラーになることを確かめる。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "error.h"
#include "symtable.h"
#include "symtable-test.h"

int lineNo;
char filename[] = "dummy";

main()
{
  string name1 = string("sameName");
  string name2 = string("otherName");

  // エラーメッセージのために，ファイル名のダミーをセット
  setFileName(filename);

  addProcedure(name1,TVoid,NULL);
  addProcedure(name2,TInt,NULL);
  addProcedure(name1,TReal,NULL);	// 同名の手続きが宣言済みなのでエラー

  printAllSymbols();
}

