#pragma implementation "symtable.h"

using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

*******************************************************************/

#include <string>
#include <map>
#include "symtable.h"
#include "error.h"

// static 関数のプロトタイプ宣言
static VarEntry *addVariable(string name, VarClass vc, Type type, 
                             bool array, int size, SymbolTable *table);
static SymbolEntry *find(string name, SymbolTable *table);


static SymbolTable globalSymTable;	// 大域的な記号表
static SymbolTable localSymTable;	// 局所的な記号表

static int localVarLocation;		// 局所変数のフレーム内相対番地
static int paramLocation;		// 仮引数のフレーム内相対番地


// プログラムのコンパイル終了後に、宣言済のユーザ手続きが
// すべて定義されたかどうかを調べる関数
// 宣言されたのに定義されていない関数があったらエラーを報告する
void checkProgram()
{
  SymbolTable::iterator it, ie = globalSymTable.end();
  // 大域的な記号表のエントリを順に調べる
  for (it=globalSymTable.begin(); it != ie; it++)  {
    SymbolEntry *symbol = it->second;
    // そのエントリがユーザ手続きエントリで、未定義ならエラーを報告する
    if (symbol->isProcedure() && !((ProcEntry *)symbol)->isDefined())
      compileError(EProcNotDefined,symbol->getName().c_str());
  }
}

// 記号表の初期化を行う関数。
// 大域的な記号表に、あらかじめmain()を登録しておく。
// こうすることで、main()はユーザが宣言する必要はなくなる。
// （定義はユーザがしなければならない）
void initializeSymbolTable()
{
  addProcedure("main", TVoid, NULL);	// main()を登録
}

// main()本体の中間コードを記号表から取り出す関数
// インタプリタが中間コードを実行するときは、main()本体の中間コード
// から実行を開始する。コンパイルが終了した後に、インタプリタに
// main()本体の中間コードを渡すために、この関数を呼び出す。
Code *getMainCode()
{
  // main()のエントリを大域的な記号表から取り出す（checkProgram()により、
  // main()が定義済であることをチェックしてからこの関数を呼び出す。
  // そうすれば、ここでmain()が定義済かチェックする必要はない）
  ProcEntry *proc = (ProcEntry *)globalSymTable.find(string("main"))->second;
  return proc->getCode();
}

// 大域変数のための変数エントリを生成し、大域的な記号表に登録する
// 登録した変数エントリへのポインタを返す
課題７で作成した関数 addGlobalVariable() の定義をここにペースト（この行は削除すること）

// 配列のための変数エントリを生成し、大域的な記号表に登録する
// 登録した変数エントリへのポインタを返す
課題７で作成した関数 addArray() の定義をここにペースト（この行は削除すること）

// 局所変数のための変数エントリを生成し、局所的な記号表に登録する
// 登録した変数エントリへのポインタを返す
課題７で作成した関数 addLocalVariable() の定義をここにペースト（この行は削除すること）

// 仮引数のための変数エントリを生成し、局所的な記号表に登録する
// 登録した変数エントリへのポインタを返す
課題７で作成した関数 addParameter() の定義をここにペースト（この行は削除すること）

// 識別子名nameと変数の種別vcをもつ変数エントリを生成し、
// tableが指す記号表にその変数エントリを登録する
// 登録した変数エントリへのポインタを返す
課題７で作成した static 関数 addVariable() の定義をここにペースト（この行は削除すること）

ProcEntry *addProcedure(string name, Type type, ParamList *params)
{

}

ProcEntry *defineProcedure(string name, Type type)
{

}

// 識別子名nameをもつ変数エントリを記号表から探し、
// 見つかったらその変数エントリへのポインタを返す
// 見つからなければエラー
VarEntry *findVariable(string name)
{
  SymbolEntry *var = find(name,&localSymTable);

  // 局所的な記号表に識別子nameをもつ記号表エントリがなければ、
  // 大域的な記号表から識別子nameをもつ記号表エントリを探す
  if (var == NULL)
    var = find(name,&globalSymTable);

  // 記号表エントリが見つからなければエラー
  if (var == NULL)
    compileError(EVarNotDeclared,name.c_str());
  // 手続きエントリが見つかったらエラー
  else if (var->isProcedure())
    compileError(EDeclaredAsProc,name.c_str());
  // 見つかった変数エントリへのポインタを返す
  else
    return (VarEntry *)var;
}

ProcEntry *findProcedure(string name)
{

}

// 識別子名nameをもつ記号表エントリを、tableが指す記号表から探す
// 見つかったらその記号表エントリへのポインタを、見つからなければ
// NULLを返す
static SymbolEntry *find(string name, SymbolTable *table)
{
  SymbolTable::iterator it = table->find(name);
  if (it == table->end())
    return NULL;
  else
    return it->second;
}

// 手続き定義の仮引数リストと手続き宣言の仮引数リストを比較し、
// 引数の個数と、対応する引数の型が、それぞれ一致することをチェックする。
// 一致しなければエラー。一致すれば、何もせずにリターン。
void checkParamList(ParamList *params, ProcEntry *proc)
{

}
