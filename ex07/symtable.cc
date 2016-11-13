#pragma implementation "symtable.h"

using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．
s1220091 国分佑太朗$
s1220228 海老原圭吾$
s1220233 小松凌也$
s1220244 向佐裕貴$
*******************************************************************/

#include "symtable.h"
#include "error.h"

// static 関数のプロトタイプ宣言
static VarEntry *addVariable(string name, VarClass vclass, Type type,
                             bool array, int size, SymbolTable *table);
static SymbolEntry *find(string name, SymbolTable *table);


static SymbolTable globalSymTable;	// 大域的な記号表
static SymbolTable localSymTable;	// 局所的な記号表

// 大域変数のための変数エントリを生成し、大域的な記号表に登録する
// 登録した変数エントリへのポインタを返す
VarEntry *addGlobalVariable(string name, Type type)
{
  //大域的な記号表(globalSymTable)は大域変数と手続きのためのものであるが
  //この関数内では前者に対してのみ行う形を取る。
  //実際に変数エントリを作成、登録するのはaddVariable()なので
  //VarClassだけ大域変数のものを指定して渡すようにした。
  
  return addVariable(name,GlobalVar,type,false,0,&globalSymTable);
}

// 配列のための変数エントリを生成し、大域的な記号表に登録する
// 登録した変数エントリへのポインタを返す
VarEntry *addArray(string name, Type type, int size)
{
  return addVariable(name,GlobalVar,type,true,size,&globalSymTable);
}

// 局所変数のための変数エントリを生成し、局所的な記号表に登録する
// 登録した変数エントリへのポインタを返す
VarEntry *addLocalVariable(string name, Type type)
{
  //局所的な記号表(localSymTable)は局所変数と仮引数のためのものであるが
  //この関数内では前者に対してのみ行う形を取る。
  //実際に変数エントリを作成、登録するのはaddVariable()なので
  //VarClassだけ局所変数のものを指定して渡すようにした。
  
  VarEntry *var = addVariable(name,LocalVar,type,false,0,&localSymTable);
  return var;
}

// 仮引数のための変数エントリを生成し、局所的な記号表に登録する
// 登録した変数エントリへのポインタを返す
VarEntry *addParameter(string name, Type type)
{
  // 局地的な記号表に，渡されたパラメタを配列じゃないことを明示して追加する
  VarEntry *var = addVariable(name, Param, type, false, 0, &localSymTable);
  return var;
}

// 識別子名name、変数の種別vc、型type、配列かどうかを示すフラグarray、
// 配列のサイズsizeをもつ変数エントリを生成し、
// tableが指す記号表にその変数エントリを登録する
// 登録した変数エントリへのポインタを返す
static VarEntry *addVariable(string name, VarClass vc, Type type, 
                             bool array, int size, SymbolTable *table)
{
  // この関数の本体を変更すること

  // 同じ名前の識別子が与えられた記号表に存在するかチェック、あればエラー
  SymbolEntry *symbol = find(name,table);
  if (symbol != NULL)  {
    if (symbol->isVariable())
      compileError(EVarDuplicated,name.c_str());
    else
      compileError(EAlreadyAsProc,name.c_str());
  }
  // なければ識別子名name、種別vclassの変数を生成し、与えられた記号表に登録
  VarEntry *var = new VarEntry(vc,name,type,array,size);
  table->insert(make_pair(name, var));
  return var;
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
