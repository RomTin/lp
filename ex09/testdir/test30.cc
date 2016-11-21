/****************************************************************************
  テスト３０： クラスProcEntryのメンバ関数setSystemProcedure() のテスト
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
      返り値は変数に保存しておく。
  (2) setSystemProcedure() を呼び出し、システム手続きへのポインタを
      手続きエントリに保存する。
  (3) getSystemProcedure() との結果とシステム手続きへのポインタが
      一致することを確かめる。

****************************************************************************/

#pragma implementation "code.h"

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "symtable-test.h"
#include "code.h"

int lineNo;
static void dummyFun(void);


main()
{
  Code::iterator it;
  Code *code;

  // 記号表への手続きの登録
  ProcEntry *proc1 = addProcedure(string("aCommand"),TVoid,NULL);

  // システム手続きへのポインタをコマンドと関数に保存
  proc1->setSystemProcedure(dummyFun);

  // コマンドに保存されたシステム手続きを取り出す
  SystemProc system = proc1->getSystemProcedure();
  if (system == dummyFun)
    printf("%sにはシステム手続きが正しく保存されています\n",
           proc1->getName().c_str());
  else
    printf("%sに保存されているシステム手続きは正しくありません\n",
           proc1->getName().c_str());
  // システム手続きを実行してみる
  system();
}

static void dummyFun(void)
{
  printf("It's a dummy function\n");
}

