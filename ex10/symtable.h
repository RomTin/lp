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
class SymbolEntry  {
  SymClass _class;	// 記号表エントリの種別
  string _name;		// 識別子名（エラー出力用）
  Type _type;		// 型
 public:
  // コンストラクタ
  SymbolEntry(SymClass c, string name, Type type);
  // 記号表エントリの種別を調べるための述語
  bool isVariable();
  bool isProcedure();
  // 識別子名にアクセスするためのメンバ関数
  string getName();
  // 識別子の型にアクセスするためのメンバ関数
  Type getType();
};

// 記号表の型名の定義
typedef map<string, SymbolEntry *> SymbolTable;


// 変数エントリ（記号表エントリのサブクラス）
class VarEntry : public SymbolEntry {
  VarClass _vclass;	// 変数の種別
  int _location;	// 大域変数のとき: 変数の静的データ領域内の番地
			// それ以外のとき: 変数のフレーム内相対番地
  bool _array;		// 配列なら true、単純変数なら false
  int _size;		// 配列のサイズ
 public:
  // コンストラクタ
  VarEntry(VarClass vc, string name, Type type, bool array, int size);
  // 変数の種別を調べるための述語
  bool isGlobalVariable();
  bool isLocalVariable();
  bool isParameter();
  // 変数に割り当てられた番地にアクセスするためのメンバ関数
  int getLocation();
  void setLocation(int location);
  // 配列かどうかを調べるためのメンバ関数
  bool isArray();
  // 配列のサイズを得るためのメンバ関数
  int getArraySize();
};

// 仮引数の型(型と引数名のペア)
typedef pair<Type,string> ParamType;

// 仮引数リストの型(仮引数の型のベクタ)
typedef vector<ParamType> ParamList;

// 手続きエントリ（記号表エントリのサブクラス）
class ProcEntry : public SymbolEntry {
  ParamList *_params;	// 仮引数リストへのポインタ
  Code *_code;		// 手続き本体の中間コードへのポインタ
  SystemProc _sysProc;	// システム手続きでなければNULL
  bool _defined;	// 定義済フラグ(定義済ならtrue、未定義ならfalse)
 public:
  // コンストラクタ
  ProcEntry(Type type, string name, ParamList *params);
  // 引数個数へのアクセス
  int getParamNumber();
  // 引数の型リストのポインタへのアクセス
  ParamList *getParamList();
  // 本体のコードのポインタへのアクセス
  Code *getCode();
  // 定義済フラグへのアクセス
  bool isDefined();
  void define();
  SystemProc getSystemProcedure();
  void setSystemProcedure(SystemProc sysProc);
  // 手続き本体の中間コードに構文木へのポインタを追加する
  void push_back(STree *tree);
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
