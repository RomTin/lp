#include <stdio.h>
#include <stdlib.h>
#include "symtable.cc"
#include "symtable-test.h"
#include "error.h"


// globalSymTable と localSymTable に保存された
// すべての記号表エントリを出力する関数
void printAllSymbols()
{
  SymbolTable::iterator it, ie;

  // 大域的な記号表の内容の出力
  printAllGlobalSymbols();

  printf("\n*** 局所的な記号表の内容 ***\n");
  ie = localSymTable.end();
  for (it=localSymTable.begin(); it != ie; it++)
    printSymbol(it->second);
}

// globalSymTable に保存されたすべての記号表エントリを出力する関数
void printAllGlobalSymbols()
{
  SymbolTable::iterator it, ie;

  printf("\n*** 大域的な記号表の内容 ***\n");
  ie = globalSymTable.end();
  for (it=globalSymTable.begin(); it != ie; it++)
    printSymbol(it->second);
}

// symbolが指す記号表エントリを出力する関数
void printSymbol(SymbolEntry *symbol)
{
  if (symbol->isVariable())  {
    printf("変数: %s ",symbol->getName().c_str());
    if (((VarEntry *)symbol)->isGlobalVariable())
      printf("(大域変数)\n");
    else if (((VarEntry *)symbol)->isLocalVariable())
      printf("(局所変数)\n");
    else if (((VarEntry *)symbol)->isParameter())
      printf("(仮引数)\n");
    else
      printf("(？？？)\n");
    printf("  位置 = %d\n",((VarEntry *)symbol)->getLocation());
    printf("  型 = %s\n", typeString(symbol->getType()).c_str());
  }
  else if (symbol->isProcedure())  {
    printf("手続き: %s\n",symbol->getName().c_str());
    printf("  型 = %s\n", typeString(symbol->getType()).c_str());
    int n = ((ProcEntry *)symbol)->getParamNumber();
    printf("  引数個数 = %d\n",n);
    ParamList *params = ((ProcEntry *)symbol)->getParamList();
    for (int i=0; i<n; i++)  {
      printf("  引数 %d: %s %s\n",i+1, typeString((*params)[i].first).c_str(),
             (*params)[i].second.c_str() );
    }
    printf("  コードのサイズ = %d\n",
             ((ProcEntry *)symbol)->getCode()->size());
    printf("  定義済フラグ = %d\n",((ProcEntry *)symbol)->isDefined());
    printf("  システム手続きへのポインタ = %x\n",
             ((ProcEntry *)symbol)->getSystemProcedure());
  }
  else
    printf("？？？: %s\n",symbol->getName().c_str());
}
