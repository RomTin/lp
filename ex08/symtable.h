#pragma interface

#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <string>
#include <map>
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
  int _location;	// 変数に割り当てられるデータ領域の番地
  bool _array;		// 配列なら true、単純変数なら false
  int _size;		// 配列のサイズ
 public:
  // コンストラクタ
  VarEntry(VarClass vc, string name, Type type, bool array, int size);
  // 変数の種別を調べるための述語
  bool isGlobalVariable();
  bool isLocalVariable();
  bool isParameter();
  // 変数に割り当てられるデータ領域の番地にアクセスするためのメンバ関数
  int getLocation();
  void setLocation(int location);
  // 配列かどうかを調べるためのメンバ関数
  bool isArray();
  // 配列のサイズを得るためのメンバ関数
  int getArraySize();
};


/* symboltable.cc 中の関数プロトタイプ宣言 */

VarEntry *addGlobalVariable(string name, Type type);
VarEntry *addArray(string name, Type type, int size);
VarEntry *addLocalVariable(string name, Type type);
VarEntry *addParameter(string name, Type type);
VarEntry *findVariable(string name);

#endif
