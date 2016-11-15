%{
using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．
  s1220091 国分佑太朗
  s1220228 海老原圭吾
  s1220233 小松凌也
  s1220244 向佐裕貴
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include "const.h"
#include "code.h"
#include "symtable.h"
#include "interpret.h"
#include "scanner.h"
#include "error.h"

// 関数のプロトタイプ宣言
template <typename Tnum>
static int allocateGlobalVar(VarEntry *var, Tnum val);
static void allocateArray(VarEntry *var);
static int allocateGlobalIntVar(int val);
static int allocateGlobalIntVar(double val);
static int allocateGlobalRealVar(int val);
static int allocateGlobalRealVar(double val);
static AssignTree *makeAssignTree(VarEntry *var,
                                  ExprTree *expr, ExprTree *index);
static ExprTree *makeBinExprTree(CConst op, ExprTree *lexp, ExprTree *rexp);
static RelationTree *makeRelationTree(CConst op, ExprTree *e1, ExprTree *e2);

/*
   静的変数
*/
static Code *compiled;  // 中間コードを保存する変数

// 相続属性
VarEntry *var;          // vinit の相続属性
%}

%union{
  CConst op;            // 演算子を表す定数
  string *symbol;       // 識別子名へのポインタ
  VarEntry *var;        // 変数エントリへのポインタ
  STree *tree;          // 構文木へのポインタ
  ExprTree *expression; // 式の構文木へのポインタ
  int inum;             // 整数
  double rnum;          // 実数
  Code *code;           // 中間コードへのポインタ
  CondList *condlist;   // 条件と文リストのペアの列
  CondTree *condition;  // 条件の構文木へのポインタ
  Type type;            // 変数の型
  int loc;              // 番地
}

%token <symbol> ID
%token <inum> INUM
%token <rnum> RNUM
%token <op> ADDOP MULOP RELOP LOGOP ULOGOP SIGNOP
%token IF ELSIF ELSE WHILE REPEAT RETURN
%token VOID INT REAL

%type <type> type
%type <inum> iconst
%type <rnum> rconst
%type <tree> stmt
%type <expression> expr
%type <condition> cond
%type <condlist> ifPart
%type <code> stmtList elsePart
%type <loc> vinit
%type <var> vname


%left LOGOP
%nonassoc ULOGOP
%left ADDOP
%left MULOP
%nonassoc SIGNOP

%%

// プログラム → 宣言部 代入部
program
  : declPart stmtList { compiled = $2; }
  ;

// 宣言部 → ε | 宣言部 宣言
declPart
  : /* 空列 */
  | declPart decl
  ;

// 宣言 → type ID 変数初期化子 ';' | type ID '[' INUM ']' ';'
decl
  : type ID
      { $<var>$ = addGlobalVariable(*$2,$1); var = $<var>$; }
    vinit ';'
      { $<var>3->setLocation($4); registerVariable($<var>3);
        delete $2; }
  | type ID '[' INUM ']' ';'
      { allocateArray(addArray(*$2,$1,$4)); delete $2; }
  ;

// 変数初期化子 → ε | '=' 整数定数 | '=' 実数定数
vinit
  : /* 空列 */ { $$ = allocateGlobalVar(var,0); }
  | '=' iconst
      { $$ = allocateGlobalVar(var,$2); }
  | '=' rconst
      { $$ = allocateGlobalVar(var,$2); }
  ;

// 整数定数 → INUM | SIGNOP INUM
iconst
  : INUM                    { $$ = $1; }
  | ADDOP INUM %prec SIGNOP { $$ = $1 == Cadd ?  $2 : -$2; }
  ;

// 実数定数 → RNUM | SIGNOP RNUM
rconst
  : RNUM                    { $$ = $1; }
  | ADDOP RNUM %prec SIGNOP { $$ = $1 == Cadd ?  $2 : -$2; }
  ;

// 型 → INT | REAL
type
  : INT  { }
  | REAL { }
  ;

// 文リスト → ε | 文リスト 文
stmtList
  : /* 空列 */    { $$ = new Code; }
  | stmtList stmt { $1->push_back($2); $$ = $1; }
  ;

// 文 → ID '=' 式 ';' | ID '[' 式 ']' '=' 式 ';' | if部 else部
//     | WHILE '(' 条件 ')' '{' 文リスト '}'
//     | REPEAT '(' 式 ')' '{' 文リスト '}'
// Yacc では、最初の２つの右辺中の ID は、非終端記号 vname で
// 置き換えられる。
stmt
  : vname '='
      { }
    expr ';'
      { }
  | vname '['
      { }
    expr ']'
      { }
    '=' expr ';'
      { }
  | ifPart elsePart { $$ = new IfTree($1,$2); }
  | WHILE '(' cond ')' '{' stmtList '}' { $$ = new WhileTree($3,$6); }
  | REPEAT '(' expr ')'
      { }
    '{' stmtList '}' { $$ = new RepeatTree($3,$7); }
  ;

// if部 → IF '(' 条件 ')' '{' 文リスト '}' |
//         if部 ELSIF '(' 条件 ')' '{' 文リスト '}'
ifPart
  : IF '(' cond ')' '{' stmtList '}'
      { $$ = new CondList;
        $$->push_back(make_pair($3,$6)); }
  | ifPart ELSIF '(' cond ')' '{' stmtList '}'
      { $$->push_back(make_pair($4,$7)); }
  ;

// else部 → ε | ELSE '{' 文リスト '}'
elsePart
  : /* 空列 */  { $$ = NULL; }
  | ELSE '{' stmtList '}' { $$ = $3; }
  ;

// 式 → 式 ADDOP 式 | 式 MULOP 式 | SIGNOP 式 | '(' 式 ')'
//     | ID | ID '[' 式 ']' | INUM | RNUM
// Yacc では、右辺に現れる２つの ID は、非終端記号 vname で
// 置き換えられる。
expr
  : expr ADDOP expr { $$ = makeBinExprTree($2,$1,$3); }
  | expr MULOP expr { $$ = makeBinExprTree($2,$1,$3); }
  | ADDOP expr %prec SIGNOP { $$ = new UniExprTree($1,$2); }
  | '(' expr ')' { $$ = $2; }
  | vname
      { }
  | vname '['
      { }
    expr ']'
      { }
  | INUM { }
  | RNUM { }
  ;

// stmt と expr の右辺中の ID を置き換えたもの
vname
  : ID { $$ = findVariable(*$1); }
  ;

// 条件 → 条件 LOGOP 条件 | ULOGOP 条件 | 式 RELOP 式 | '(' 条件 ')'
cond
  : cond LOGOP cond { $$ = new BinCondTree($2,$1,$3); }
  | ULOGOP cond     { $$ = new UniCondTree($1,$2); }
  | expr RELOP expr { $$ = makeRelationTree($2,$1,$3); }
  | '(' cond ')'    { $$ = $2; }
  ;

%%

template <typename Tnum>
static int allocateGlobalVar(VarEntry *var, Tnum val)
{
  switch (var->getType())  {
  case TInt:
    return allocateGlobalIntVar(val);
  case TReal:
    return allocateGlobalRealVar(val);
  default:
    compileError(EVoidVariable,var->getName().c_str());
  }
}

static int allocateGlobalIntVar(int val)
{
  return allocateMemory(val);
}

static int allocateGlobalIntVar(double val)
{
  return allocateMemory((int)val);
}

static int allocateGlobalRealVar(int val)
{
  return allocateMemory((double)val);
}

static int allocateGlobalRealVar(double val)
{
  return allocateMemory(val);
}

static void allocateArray(VarEntry *var)
{
  Type type = var->getType();
  int size = var->getArraySize();
  if (type == TVoid)
    compileError(EVoidVariable,var->getName().c_str());
  else  {
    if (size == 0)
      compileError(EIllegalSize,var->getName().c_str());
    var->setLocation(allocateGlobalVar(var,0));
    for (int i=1; i<size; i++)
      allocateGlobalVar(var,0);
    registerVariable(var);
  }
}

static AssignTree *makeAssignTree(VarEntry *var,
                                  ExprTree *expr, ExprTree *index)
{

}

static ExprTree *makeBinExprTree(CConst op, ExprTree *lexp, ExprTree *rexp)
{

}

static RelationTree *makeRelationTree(CConst op, ExprTree *e1, ExprTree *e2)
{

}

void usage(char *cmd)
{
  fprintf(stderr,"利用法: %s 原始プログラムファイル名\n",cmd);
  exit(2);
}

main(int argc, char **argv)
{
  char *cmd = *argv;    // コンパイラのコマンド名
#if YYDEBUG
  extern int yydebug;

  yydebug = 1;  /* デバッグ表示付きの構文解析系を生成したいとき 1 を代入 */
#endif

  if (argc < 2)
    usage(cmd);

  setFileName(*++argv);
  initializeScanner(*argv);
  yyparse();
  interpret(compiled);
}
