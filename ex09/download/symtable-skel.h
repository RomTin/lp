#pragma interface

#ifndef __TGLC_SYMTABLE_H__
#define __TGLC_SYMTABLE_H__

using namespace std;

#include <string>
#include <map>
#include "code.h"
#include "const.h"

// 記号表エントリの種別  SymVar: 変数, SymProc: 手続き
enum SymClass { SymVar, SymProc };

// 変数の種別  GlobalVar: 大域変数, LocalVar: 局所変数，Param: 仮引数
enum VarClass { GlobalVar, LocalVar, Param };


// 記号表エントリ 
課題７で作成したクラス SymbolEntry をここにペースト（この行は削除すること）

// 記号表の型名の定義
typedef map<string, SymbolEntry *> SymbolTable;


// 変数エントリ（記号表エントリのサブクラス）
課題７で作成したクラス VarEntry をここにペースト（この行は削除すること）

// 仮引数の型(型と引数名のペア)
typedef pair<Type,string> ParamType;

// 仮引数リストの型(仮引数の型のベクタ)
typedef vector<ParamType> ParamList;

// 手続きエントリ（記号表エントリのサブクラス）
class ProcEntry : public SymbolEntry {
  ParamList *_params;	// 仮引数リストへのポインタ(仮引数リストが空のときはNULL)
  Code *_code;		// 手続き本体の中間コードへのポインタ
  SystemProc _sysProc;	// システム手続きでなければNULL
  bool _defined;	// 定義済フラグ(定義済ならtrue、未定義ならfalse)
 public:
  // コンストラクタ
  ProcEntry(Type type, string name, ParamList *params)
    : SymbolEntry(SymProc,name,type) { }
  // 引数個数へのアクセス
  int getParamNumber() { }
  // 引数の型リストのポインタへのアクセス
  ParamList *getParamList() { }
  // 本体のコードのポインタへのアクセス
  Code *getCode() { return _code; }
  // 定義済フラグへのアクセス
  bool isDefined() { return _defined; }	// 定義済か？
  void define() { _defined = true; }	// 定義済にする
  SystemProc getSystemProcedure() { return _sysProc; }
  void setSystemProcedure(SystemProc sysProc) { _sysProc = sysProc; }
  // 手続き本体の中間コードに構文木へのポインタを追加する
  void push_back(STree *tree) { _code->push_back(tree); }
};

/* symboltable.cc 中の関数プロトタイプ宣言 */

void initializeSymbolTable(void);
void checkProgram(void);
Code *getMainCode(void);
VarEntry *addGlobalVariable(string name, Type type);
VarEntry *addArray(string name, Type type, int size);
VarEntry *addLocalVariable(string name, Type type);
VarEntry *addParameter(string name, Type type);
ProcEntry *addProcedure(string name, Type type, ParamList *params);
ProcEntry *defineProcedure(string name, Type type);
VarEntry *findVariable(string name);
ProcEntry *findProcedure(string name);
void checkParamList(ParamList *params, ProcEntry *proc);

#endif
