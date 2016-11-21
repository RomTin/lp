#pragma interface

#ifndef __TGLC_CODE_H__
#define __TGLC_CODE_H__

#include <utility>
#include <string>
#include <vector>
#include "const.h"


// 構文木の種別を表す型 STreeID の定義
//    Sreturn:    return文
//    SlocalVar: 局所変数宣言
//    Sassign:   代入文
//    Sif:       if文
//    Swhile:    while文
//    Srepeat:   repeat文
//    Sexpr:     式
//    Scond:     条件
enum STreeID { Sreturn, SlocalVar, Sassign, Sif, Swhile, Srepeat, 
               Sexpr, Scond };

// 式の構文木の種別を表す型 ExprTreeID の定義
//    ETbinop:    二項演算子をもつ式
//    ETuniop:    単項演算子をもつ式
//    ETvar:      変数
//    ETinum:     整数
//    ETrnum:     実数
//    ETarray:    配列要素
//    ETcall:     手続き呼び出し
enum ExprTreeID { ETbinop, ETuniop, ETvar, ETinum, 
                  ETrnum, ETarray, ETcall };

// 条件の構文木の種別を表す型 CondTreeID の定義
//    CTbinop:    二項論理演算子をもつ条件
//    CTuniop:    単項論理演算子をもつ条件
//    CTrel:      関係演算子をもつ条件
enum CondTreeID { CTbinop, CTuniop, CTrel };

// 変数の種別を表す型 VarID の定義
//    Vsmpl:  単純変数
//    Varray: 配列
enum VarID { Vsmpl, Varray };


// 構文木のクラス STree
class STree  {
  STreeID _id;		// 構文木の種別
 public:
  // コンストラクタ
  STree(STreeID id) : _id(id) { }
  // 構文木の種別を返すメンバ関数
  STreeID getID() { return _id; }
};

// 中間コードの型 Code の定義
typedef vector<STree *> Code;


// 式の構文木
class ExprTree : public STree {
  ExprTreeID _id;
  Type _type;
 public:
  // コンストラクタ
  ExprTree(ExprTreeID id, Type type)
    : STree(Sexpr), _id(id), _type(type) { }
  // 式の構文木の種別を返すメンバ関数
  ExprTreeID getID() { return _id; }
  // 式の型を返すメンバ関数
  Type getType() { return _type; }
};

// 二項演算子をもつ式の構文木
class BinExprTree : public ExprTree {
  CConst _operator;	// 演算子を表す定数
  ExprTree *_operand1;	// 左の引数の構文木へのポインタ
  ExprTree *_operand2;	// 右の引数の構文木へのポインタ
 public:
  // コンストラクタ
  BinExprTree(CConst op, ExprTree *op1, ExprTree *op2)
    : ExprTree(ETbinop, op1->getType())  {
    _operator = op; _operand1 = op1; _operand2 = op2;
  }
  // メンバにアクセスするためのメンバ関数
  CConst getOperator() { return _operator; }
  ExprTree *getFirstOperand() { return _operand1; }
  ExprTree *getSecondOperand() { return _operand2; }
};

// 単項演算子をもつ式の構文木
class UniExprTree : public ExprTree {
  CConst _operator;	// 演算子を表す定数
  ExprTree *_operand;	// 引数の構文木へのポインタ
 public:
  // コンストラクタ (Cint2real, Creal2int 以外)
  UniExprTree(CConst op, ExprTree *op1)
    : ExprTree(ETuniop, op1->getType())  {
    _operator = op; _operand = op1;
  }
  // コンストラクタ (Cint2real, Creal2int のとき)
  UniExprTree(CConst op, ExprTree *op1, Type type)
    : ExprTree(ETuniop, type)  {
    _operator = op; _operand = op1;
  }
  // メンバにアクセスするためのメンバ関数
  CConst getOperator() { return _operator; }
  ExprTree *getOperand() { return _operand; }
};

// 変数
class Variable  {
  VarID _id;	// 変数の種別
  string _name; // 変数名
  int _loc;     // 変数のメモリ上の番地
  bool _global;	// 大域変数かどうかを表すフラグ
 public:
  Variable(VarID id, string name, int loc, bool global)  {
    _id = id; _name = name; _loc = loc; _global = global;
  }
  // メンバ変数にアクセスするためのメンバ関数
  bool isArray() { return (_id == Varray); }
  string getName() { return _name; }
  int getLocation() { return _loc; }
  bool isGlobal() { return _global; }
};

// 単純変数の構文木
class SmplVarNode : public ExprTree, public Variable {
 public:
  // コンストラクタ
  SmplVarNode(string name, int loc, Type type, bool global)
    : Variable(Vsmpl,name,loc,global), ExprTree(ETvar,type) { }
};

// 配列要素の構文木
class ArrayElemTree : public ExprTree, public Variable {
  ExprTree *_index;	// 配列のインデックスの式の構文木
  int _size;		// 配列のサイズ(要素数)
 public:
  // コンストラクタ
  ArrayElemTree(string name, int loc, Type type, ExprTree *index, int size)
    : Variable(Varray,name,loc,true), ExprTree(ETarray,type)  {
    _index = index;
    _size = size;
  }
  // メンバにアクセスするためのメンバ関数
  ExprTree *getIndex() { return _index; }
  int getArraySize() { return _size; }
};

// 整数の構文木
class INumNode : public ExprTree {
  int  _num;	// 値
 public:
  // コンストラクタ
  INumNode(int number) : ExprTree(ETinum,TInt)  {
    _num = number;
  }
  // メンバにアクセスするためのメンバ関数
  int getValue() { return _num; }
};

// 実数の構文木
class RNumNode : public ExprTree {
  double  _num;	// 値
 public:
  // コンストラクタ
  RNumNode(double number) : ExprTree(ETrnum,TReal)  {
    _num = number;
  }
  // メンバにアクセスするためのメンバ関数
  double getValue() { return _num; }
};

// 条件の構文木
class CondTree : public STree {
  CondTreeID _id;
 public:
  // コンストラクタ
  CondTree(CondTreeID id) : STree(Scond), _id(id) { }
  // 条件の構文木の種別を返すメンバ関数
  CondTreeID getID() { return _id; }
};

// 二項論理演算子をもつ条件の構文木
class BinCondTree : public CondTree {
  CConst _operator;	// 二項論理演算子を表す定数
  CondTree *_operand1;	// 左辺の条件の構文木へのポインタ
  CondTree *_operand2;	// 右辺の条件の構文木へのポインタ
 public:
  BinCondTree(CConst op, CondTree *op1, CondTree *op2) : CondTree(CTbinop) {
    _operator = op; _operand1 = op1; _operand2 = op2;
  }
  // メンバにアクセスするためのメンバ関数
  CConst getOperator() { return _operator; }
  CondTree *getFirstOperand() { return _operand1; }
  CondTree *getSecondOperand() { return _operand2; }
};

// 単項論理演算子をもつ条件の構文木
class UniCondTree : public CondTree {
  CConst _operator;	// 単項条件演算子を表す定数
  CondTree *_operand;	// 引数の条件の構文木へのポインタ
 public:
  // コンストラクタ
  UniCondTree(CConst op, CondTree *operand) : CondTree(CTuniop) {
    _operator = op; _operand = operand;
  }
  // メンバにアクセスするためのメンバ関数
  CConst getOperator() { return _operator; }
  CondTree *getOperand() { return _operand; }
};

// 関係演算子をもつ条件の構文木
class RelationTree : public CondTree {
  CConst _operator;	// 条件演算子を表す定数
  ExprTree *_operand1;	// 左辺の式の構文木へのポインタ
  ExprTree *_operand2;	// 右辺の式の構文木へのポインタ
 public:
  // コンストラクタ
  RelationTree(CConst op, ExprTree *op1, ExprTree *op2) : CondTree(CTrel) {
    _operator = op; _operand1 = op1; _operand2 = op2;
  }
  // メンバにアクセスするためのメンバ関数
  CConst getOperator() { return _operator; }
  ExprTree *getFirstOperand() { return _operand1; }
  ExprTree *getSecondOperand() { return _operand2; }
};

// 条件とコードのペアの列
typedef vector<pair<CondTree *, Code *> > CondList;

// 代入文の構文木
class AssignTree : public STree {
  Variable *_var;	// 左辺の変数または配列
  ExprTree *_expr;	// 代入される式の構文木へのポインタ
 public:
  // コンストラクタ
  AssignTree(Variable *var, ExprTree *expr) : STree(Sassign)  {
    _var = var; _expr = expr;
  }
  // メンバにアクセスするためのメンバ関数
  Variable *getVariable() { return _var; }
  ExprTree *getExpression() { return _expr; }
};

// if文の構文木
class IfTree : public STree {
  CondList *_cond;	// 条件と実行する文リストのペアの列
  Code *_elsePart;	// すべての条件が偽のときに実行する文リスト
 public:
  // コンストラクタ
  IfTree(CondList *cond, Code *elsePart) : STree(Sif) {
    _cond = cond; _elsePart = elsePart;
  }
  // メンバにアクセスするためのメンバ関数
  CondList *getCondList() { return _cond; }
  Code *getElsePart() { return _elsePart; }
};

// while文の構文木
class WhileTree : public STree {
  CondTree *_cond;	// 条件
  Code *_body;		// 本体
 public:
  // コンストラクタ
  WhileTree(CondTree *cond, Code *body) : STree(Swhile) {
    _cond = cond; _body = body;
  }
  // メンバにアクセスするためのメンバ関数
  CondTree *getCondition() { return _cond; }
  Code *getBody() { return _body; }
};

// repeat文の構文木
class RepeatTree : public STree {
  ExprTree *_count;	// 繰り返しの回数
  Code *_body;		// 本体
 public:
  // コンストラクタ
  RepeatTree(ExprTree *count, Code *body) : STree(Srepeat) {
    _count = count; _body = body;
  }
  // メンバにアクセスするためのメンバ関数
  ExprTree *getCount() { return _count; }
  Code *getBody() { return _body; }
};

// システム手続きを実現するC関数の型SystemProcの定義
typedef void (*SystemProc)(void);

// 引数列の型
typedef vector<ExprTree *> ArgList;

// 手続き呼び出しの構文木の定義
class CallTree : public ExprTree {
  ArgList *_args;	// 引数列
  Code *_code;		// 呼び出す手続きの本体
  string _name;		// 手続きの識別子名
  SystemProc _sysProc;	// システム手続きのときの対応するC関数
 public:
  // コンストラクタ
  CallTree(string name, Type type, ArgList *args, SystemProc sys, Code *code)
    : ExprTree(ETcall,type)  {
    _name = name; _code = code; _args = args; _sysProc = sys; }
  // メンバにアクセスするためのメンバ関数
  ArgList *getArguments() { return _args; }
  Code *getCode() { return _code; }
  string getName() { return _name; }
  SystemProc getSystemProcedure() { return _sysProc; }
  void setSystemProcedure(SystemProc proc) { _sysProc = proc; }
};

// return文の構文木
class ReturnTree : public STree {
  ExprTree *_expr;	// 返り値の式の構文木へのポインタ
  int _paramNum;	// return文を含む手続きの仮引数個数
 public:
  // コンストラクタ
  ReturnTree(ExprTree *expr, int paramNum)
    : STree(Sreturn), _expr(expr), _paramNum(paramNum) { }
  // メンバにアクセスするためのメンバ関数
  ExprTree *getExpression() { return _expr; }
  int getParamNumber() { return _paramNum; }
};

// 局所変数宣言のための構文木
class LocalVarTree : public STree {
  string _name;		// 局所変数名
  Type _type;		// 局所変数の型
  ExprTree *_expr;	// 局所変数の初期値の構文木へのポインタ
 public:
  // コンストラクタ
  LocalVarTree(string name, Type type, ExprTree *expr)
    : STree(SlocalVar), _name(name), _type(type), _expr(expr) { }
  // メンバにアクセスするためのメンバ関数
  string getName() { return _name; }
  Type getType() { return _type; }
  ExprTree *getExpression() { return _expr; }
};

#endif
