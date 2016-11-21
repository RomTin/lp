/****************************************************************************
  テスト５： addprocedure() の異常ケースのテスト３
  (1) addProcedure() を２回呼び出して、名前、型、引数リストが
      すべて同じ手続きのエントリを globalSymTable に登録する．
  (2) 以前に登録した手続きとまったく同じ手続きを登録したときでも
      エラーになることを確かめる．

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
  addProcedure(name1,TVoid,NULL);	// 同名の手続きが宣言済みなのでエラー

  printAllSymbols();
}

