#pragma interface

#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

using namespace std;

#include <string>	// ストリングを使うためのインクルードファイル
#include <map>		// マップを使うためのインクルードファイル
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
  SymbolEntry(SymClass c, string name, Type type)
  // これ以降のコンストラクタの定義を書き換えること
    : _class(c), _name(name), _type(type) { }
  // 記号表エントリの種別を調べるための述語
  bool isVariable() { return _class == SymVar; }
  bool isProcedure() { return _class == SymProc; }
  // 識別子名にアクセスするためのメンバ関数
  string getName() { return _name; }
  // 識別子の型にアクセスするためのメンバ関数
  Type getType() { return _type; }
};

// 記号表の型名の定義
typedef map<string, SymbolEntry *> SymbolTable;


// 変数エントリ（記号表エントリのサブクラス）
class VarEntry : public SymbolEntry {
  VarClass _vclass;	// 変数の種別
  int _location;	// 大域変数のとき: 変数の静的データ領域内の番地
  int _local_location; // それ以外のとき: 変数のフレーム内相対番地
  bool _array;		// 配列なら true、単純変数なら false
  int _size;		// 配列のサイズ
 public:
  // コンストラクタ
  VarEntry(VarClass vc, string name, Type type, bool array, int size)
  // これ以降のコンストラクタの定義を書き換えること
    : SymbolEntry(SymVar,name, type) {
    _vclass = vc;	// メンバ変数 _vclassの初期化
    _array = array;
    _size = size;
  }
  // 変数の種別を調べるための述語
  bool isGlobalVariable() { return _vclass == GlobalVar; }
  bool isLocalVariable() { return _vclass == LocalVar; }
  bool isParameter() { return _vclass == Param; }
  // 配列かどうかを調べるためのメンバ関数
  bool isArray() { return _array; }
  // 配列のサイズを得るためのメンバ関数
  int getArraySize() { return _size; }
};


/* symboltable.cc 中の関数プロトタイプ宣言 */

VarEntry *addGlobalVariable(string name, Type type);
VarEntry *addArray(string name, Type type, int size);
VarEntry *addLocalVariable(string name, Type type);
VarEntry *addParameter(string name, Type type);
VarEntry *findVariable(string name);

#endif
