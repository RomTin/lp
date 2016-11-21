/****************************************************************************
  テスト２９： クラスProcEntryのメンバ関数pushBack() のテスト
  (1) addProcedure() を呼び出して globalSymTable に手続きエントリを登録する。
      返り値は変数に保存しておく。
  (2) 構文木を作り、pushBack() を使って手続きエントリがもつ
      中間コードに追加する。

****************************************************************************/

#pragma implementation "code.h"

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "symtable-test.h"
#include "code.h"

int lineNo;
static void printSTree(STree *tree);


main()
{
  Code::iterator it;
  Code *code;

  // 記号表への手続きの登録
  ProcEntry *proc1 = addProcedure(string("aCommand"),TVoid,NULL);

  // 手続きがもつ中間コードに構文木を追加
  proc1->push_back(new STree(Swhile));
  proc1->push_back(new STree(Sreturn));
  proc1->push_back(new STree(SlocalVar));
  proc1->push_back(new STree(Swhile));
  proc1->push_back(new STree(Sif));

  // 手続きの中間コードを順に表示
  printf("%sの中間コード\n",proc1->getName().c_str());
  code = proc1->getCode();
  for (it=code->begin(); it != code->end(); it++)
    printSTree(*it);

  // globalSymTable に保存されたすべての記号表エントリを出力する．
  printAllGlobalSymbols();
}

void printSTree(STree *tree)
{
  printf("構文木: ");
  switch (tree->getID())  {
  case Sassign:
    printf("Sassign");
    break;
  case Sif:
    printf("Sif");
    break;
  case Swhile:
    printf("Swhile");
    break;
  case Srepeat:
    printf("Srepeat");
    break;
  case Sreturn:
    printf("Sreturn");
    break;
  case SlocalVar:
    printf("SlocalVar");
    break;
  case Sexpr:
    printf("Sexpr");
    break;
  case Scond:
    printf("Scond");
    break;
  }
  putchar('\n');
}

