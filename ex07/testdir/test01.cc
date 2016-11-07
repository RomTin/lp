/************************************************************************
  テスト１： VarEntry() と find() のテスト
  (1) 自分で記号表を用意する．
  (2) new VarEntry() を使って変数エントリを生成し，その記号表に登録する．
  (3) 最後に，いろいろな識別子を指定してfind()を呼び出し，登録されていれば
      対応する変数エントリへのポインタを，登録されていなければNULLを
      返すことを確かめる．

**********************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "const.h"
#include "symtable-test.h"

static void printResult(string name, SymbolEntry *symbol);

main()
{
  SymbolTable myTable;
  VarEntry *var;
  string varname0 = string("aVariable0");
  string varname1 = string("aVariable1");
  string varname2 = string("aVariable2");
  string varname3 = string("aVariable3");
  string varname4 = string("aVariable4");
  string varname5 = string("aVariable5");
  string varname6 = string("aVariable6");
  string varname7 = string("aVariable7");
  string varname8 = string("aVariable8");
  string varname9 = string("aVariable9");

  // 変数エントリを直接生成し，記号表 myTable に直接登録する
  var = new VarEntry(LocalVar,varname1,TInt,false,0);
  myTable.insert(make_pair(varname1,(SymbolEntry *)var));
  var = new VarEntry(GlobalVar,varname2,TReal,false,0);
  myTable.insert(make_pair(varname2,(SymbolEntry *)var));
  var = new VarEntry(Param,varname3,TInt,false,0);
  myTable.insert(make_pair(varname3,(SymbolEntry *)var));
  var = new VarEntry(GlobalVar,varname4,TInt,true,20);
  myTable.insert(make_pair(varname4,(SymbolEntry *)var));
  var = new VarEntry(LocalVar,varname5,TReal,false,0);
  myTable.insert(make_pair(varname5,(SymbolEntry *)var));

  // 内部で find() を呼び出す関数 findG() （symtable-test.ccで定義）を
  // 呼び出し，変数エントリが見つかったかどうかをチェックする．
  printResult(varname3, findG(varname3,&myTable));	// 見つかる
  printResult(varname8, findG(varname8,&myTable));	// 見つからない
  printResult(varname7, findG(varname7,&myTable));	// 見つからない
  printResult(varname5, findG(varname5,&myTable));	// 見つかる
  printResult(varname1, findG(varname1,&myTable));	// 見つかる
  printResult(varname3, findG(varname3,&myTable));	// 見つかる
  printResult(varname9, findG(varname9,&myTable));	// 見つからない
  printResult(varname5, findG(varname5,&myTable));	// 見つかる
  printResult(varname4, findG(varname4,&myTable));	// 見つかる
  printResult(varname0, findG(varname0,&myTable));	// 見つからない
  printResult(varname7, findG(varname7,&myTable));	// 見つからない
  printResult(varname6, findG(varname6,&myTable));	// 見つからない
  printResult(varname2, findG(varname2,&myTable));	// 見つかる
}


// 変数エントリが見つかったら「見つかりました」，見つからなければ
// 「見つかりません」と出力する関数
static void printResult(string name, SymbolEntry *symbol)
{
  if (symbol == NULL)
    printf("変数%sが見つかりません\n",name.c_str());
  else  {
    printf("変数%sが見つかりました\n",name.c_str());
  }
}
