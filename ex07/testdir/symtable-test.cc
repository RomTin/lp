#include <stdio.h>
#include "symtable.cc"
#include "symtable-test.h"
#include "error.h"

int lineNo;

// addVariable() を symtable.cc の外からも呼び出せるようにするための関数
// このファイルは，symtable.cc をインクルードしているので，addVariable()
// を呼び出せる．
VarEntry *addVariableG(string name, VarClass vc, Type type,
                       bool array, int size, SymbolTable *table)
{
  return addVariable(name,vc,type,array,size,table);
}

// テスト用に手続きエントリを生成し，globalSymTable に登録する関数
// テスト用なので，エラー処理はいっさい行わない．返り値も返さない．
void addProcedure(string name, Type type)
{
  SymbolEntry *symbol = new SymbolEntry(SymProc,name,type);
  globalSymTable.insert(make_pair(name,symbol));
}

// find() を symtable.cc の外からも呼び出せるようにするための関数
// このファイルは，symtable.cc をインクルードしているので，find()を
// 呼び出せる．
SymbolEntry *findG(string name, SymbolTable *table)
{
  return find(name,table);
}

// globalSymTable と localSymTable に保存されたすべての変数エントリを
// 出力する関数
void printAllSymbols()
{
  SymbolTable::iterator it, ie;

  printf("*** 大域的な記号表の内容 ***\n");
  ie = globalSymTable.end();
  for (it=globalSymTable.begin(); it != ie; it++)
    printSymbol(it->second);

  printf("*** 局所的な記号表の内容 ***\n");
  ie = localSymTable.end();
  for (it=localSymTable.begin(); it != ie; it++)
    printSymbol(it->second);
}

// symbolが指す記号表エントリを出力する関数
void printSymbol(SymbolEntry *symbol)
{
  if (symbol->isVariable())  {
    // 変数名、型、変数の種別を出力する
    printf("変数: %s (型: %s)",
           symbol->getName().c_str(),getTypeStr(symbol->getType()).c_str());
    if (((VarEntry *)symbol)->isGlobalVariable())
      printf("(大域変数) ");
    else if (((VarEntry *)symbol)->isLocalVariable())
      printf("(局所変数) ");
    else if (((VarEntry *)symbol)->isParameter())
      printf("(仮引数) ");
    else
      printf("(？？？)\n");
    // 配列か単純変数かを出力する
    if (((VarEntry *)symbol)->isArray())
      printf("(配列) サイズ: %d\n", 
             ((VarEntry *)symbol)->getArraySize());
    else
      printf("(単純変数)\n");
  }
  else if (symbol->isProcedure())  {
    printf("手続き: %s\n",symbol->getName().c_str());
  }
  else
    printf("？？？: %s\n",symbol->getName().c_str());
}
