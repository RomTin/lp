#pragma implementation "symtable.h"

using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．
  s1220091 国分佑太朗
  s1220228 海老原圭吾
  s1220233 小松凌也
  s1220244 向佐裕貴
 *******************************************************************/

#include <vector>
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
{// 配列であることを表すためにtrueとsizeを渡している
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
  var->setLocation(localVarLocation++);
  return var;
}


// 仮引数のための変数エントリを生成し、局所的な記号表に登録する
// 登録した変数エントリへのポインタを返す
VarEntry *addParameter(string name, Type type)
{
  // 局地的な記号表に，渡されたパラメタを配列じゃないことを明示して追加する
  VarEntry *var = addVariable(name, Param, type, false, 0, &localSymTable);
  var->setLocation(paramLocation++);
  return var;
}


// 識別子名nameと変数の種別vcをもつ変数エントリを生成し、
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
  // VarEntryのコンストラクタの引数の変更に従って渡す変数を増やした
  VarEntry *var = new VarEntry(vc,name,type,array,size);
  table->insert(make_pair(name, var));
  return var;
}


ProcEntry *addProcedure(string name, Type type, ParamList *params)
{
  //名前nameを持つ識別子が大域的な記号表にあるかチェック
  SymbolEntry *sym = find(name, &globalSymTable);
  //記号表からエントリが見つかったのでエラーの制御に移る
  if(sym != NULL){
    //登録済みエントリが変数エントリかチェック
    if(sym->isVariable()){
      compileError(EAlreadyAsVar, name.c_str());
    }
    //登録済みのエントリが手続きエントリかチェック
    else if(sym->isProcedure()){
      compileError(EProcDuplicated, name.c_str());
    }
  }
  //手続きエントリを生成し大域的な記号表に登録する
  ProcEntry *proc = new ProcEntry(type, name, params);
  globalSymTable.insert(make_pair(name,proc));

  return proc;
}

ProcEntry *defineProcedure(string name, Type type)
{
  ProcEntry *declaredProc = findProcedure(name);

  // 既に定義済みであればエラー
  if (declaredProc->isDefined()) {
    compileError(EProcDuplicated, name.c_str());

  } else if (declaredProc->getType() != type) {
    // 取得した手続きの戻り値の型が定義の戻り値の型と一致しなければエラー
    compileError(EProcTypeMismatch, name.c_str());
  }

  // 仮引数の数を取得
  size_t param_size = declaredProc->getParamNumber();

  // 局所変数の番地の開始地点は1で固定
  localVarLocation = 1;

  // 仮引数の番地の開始地点は引数の数*-1
  paramLocation = -param_size;

  // 局所的な記号表を初期化。
  localSymTable.clear();

  // 手続きを定義済みにする。
  declaredProc->define();
  return declaredProc;
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

// 識別子名nameの手続きエントリを大域的な記号表から探す
// 見つかったら手続きエントリへのポインタを返却し、
// 見つからなければエラー
ProcEntry *findProcedure(string name)
{
  // 大域的な記号表から識別子nameを持つ記号表エントリを探す
  SymbolEntry *var = find(name,&globalSymTable);

  // 見つからなければエラー
  if(var == NULL){
    compileError(EProcNotDeclared,name.c_str());
  }
  else if(var->isVariable()){
    // 変数として宣言されていればコンパイルエラー
    compileError(EDeclaredAsVar,name.c_str());
  }else{
    // 手続きの記号表エントリのポインタを返却する
    return (ProcEntry *)var;
  }
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
  // 引数の個数が一致しているかどうか
  if ( params->size() != proc->getParamNumber() ) {
    // 一致していなければエラー
    compileError(EParamNumMismatch, proc->getName().c_str(), params->size(), proc->getParamNumber());
  } else {

    // 手続きエントリが持つ仮引数リストを取得
    ParamList *procParams = proc->getParamList();

    // それぞれのリストの開始イテレータを取得
    ParamList::iterator it = procParams->begin();
    ParamList::iterator it2 = params->begin();

    // 型が一致しているかどうか [1,引数の個数]だけチェックを回す
    for (int i = 1; i <= params->size(); i++) {
      ParamType ptype1 = *it++;
      ParamType ptype2 = *it2++;
      // 型が一致していなければエラー
      if (ptype1 != ptype2) {
        compileError(EParamTypeMismatch, proc->getName().c_str(), i);
      }
    }
  }

}
