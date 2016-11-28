%{
using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

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
static ExprTree *makeCallTree(string name, ArgList *params, ProcEntry *callee);
static LocalVarTree *initLocalVar(string name, Type vtype, ExprTree *expr);
static ReturnTree *makeDefaultReturnTree(Type type);
static ReturnTree *makeReturnTreeWithValue(ExprTree *val);
static void addParameters(ParamList *params);

/*
   静的変数
*/
static Code *compiled;	// main()の構文木

// 相続属性
VarEntry *var;          // vinit, localvinit の相続属性
static ProcEntry *proc; // localDeclList, localDecl, localvinit, body,
                        // stmt, stmtList, ifPart, elsePart の相続属性
%}

%union{
  CConst op;		// 演算子を表す定数
  string *symbol;	// 識別子名へのポインタ
  VarEntry *var;	// 変数エントリへのポインタ
  ProcEntry *proc;	// 手続きエントリへのポインタ
  STree *tree;		// 構文木へのポインタ
  ExprTree *expression;	// 式の構文木へのポインタ
  int inum;		// 整数
  double rnum;		// 実数
  Code *code;		// 中間コードへのポインタ
  CondList *condlist;	// 条件と文リストのペアの列
  CondTree *condition;	// 条件の構文木へのポインタ
  Type type;		// 変数、手続きの型
  ParamType *param;	// 引数
  ParamList *params;	// 引数リストへのポインタ
  ArgList *args;	// 実引数リストへのポインタ
  int loc;		// 番地
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
%type <args> argList argList2
%type <param> formalParam
%type <params> formalParamList formalParamList2 
%type <loc> vinit
%type <var> vname


%left LOGOP
%nonassoc ULOGOP
%left ADDOP
%left MULOP
%nonassoc SIGNOP

%%

// プログラム → 宣言部 定義部
program
  : declPart defPart { checkProgram(); compiled = getMainCode(); }
  ;

// 宣言部 → ε | 宣言部 宣言
declPart
  : /* 空列 */
  | declPart decl
  ;

// 宣言 → type ID 変数初期化子 ';' | type ID '[' INUM ']' ';'
//      | type ID '(' 仮引数リスト ')' ';'
decl
  : type ID
      { $<var>$ = addGlobalVariable(*$2,$1); var = $<var>$; }
    vinit ';'
      { $<var>3->setLocation($4); registerVariable($<var>3);
        delete $2; }
  | type ID '[' INUM ']' ';'
      { allocateArray(addArray(*$2,$1,$4)); delete $2; }
  | type ID '(' formalParamList ')' ';'
      { addProcedure(*$2,$1,$4); delete $2; }
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

// 型 → INT | REAL | VOID
type
課題８で作成した type の定義の２行目(INT)から最後から２行目(REAL)までを、ここにコピー(この行は削除する)
  | VOID { }
  ;

// 定義部 → 手続き定義 | 定義部 手続き定義
defPart	: procDef
  | defPart procDef
  ;

// 手続き定義 → type ID '(' 仮引数リスト ')' '{' 局所宣言リスト 本体 '}'
procDef
  : type ID  '(' formalParamList ')' '{'
      { }
    localDeclList body '}' 
      { }
  ;

// 本体 → ε | 本体 文
body
  : /* 空列 */
  | body stmt  { proc->push_back($2); }
  ;

// 仮引数リスト → ε | 仮引数リスト’
formalParamList
  : /* 空列 */       { $$ = NULL; }
  | formalParamList2
  ;

// 仮引数リスト’ → 仮引数 | 仮引数リスト’',' 仮引数
formalParamList2
  : formalParam	{ $$ = new ParamList; $$->push_back(*$1); delete $1; }
  | formalParamList2 ',' formalParam
      { $$ = $1; $$->push_back(*$3); delete $3; }
  ;

// 仮引数 → 型 ID
formalParam
  : type ID
      { }
  ;

// 局所宣言リスト → ε | 局所宣言リスト 局所宣言
localDeclList
  : /* 空列 */
  | localDeclList localDecl
  ;

// 局所宣言 → 型 ID 局所変数初期化子 ';'
localDecl
  : type ID
      { }
    localvinit ';' { delete $2; }
  ;

// 局所変数初期化子 → ε | '=' 式
localvinit
  : /* 空列 */
      { proc->push_back(new LocalVarTree(var->getName(),var->getType(),NULL)); }
  | '=' expr
      { proc->push_back(initLocalVar(var->getName(),var->getType(),$2)); }
  ;

// 文リスト → ε | 文リスト 文
stmtList
  : /* 空列 */    { $$ = new Code; }
  | stmtList stmt { $1->push_back($2); $$ = $1; }
  ;

// 文 → ID '=' 式 ';' | ID '[' 式 ']' '=' 式 ';' | if部 else部
//     | WHILE '(' 条件 ')' '{' 文リスト '}'
//     | REPEAT '(' 式 ')' '{' 文リスト '}'
//     | ID '(' 実引数リスト ')' ';'
//     | RETURN ';'
//     | RETURN 式 ';'
// Yacc では、最初の２つの右辺中の ID は、非終端記号 vname で
// 置き換えられる。
stmt
課題８で作成した stmt の定義の２行目(vname '=' ...)から最後から２行目(REPEAT)までを、ここにコピー(この行は削除する)
  | ID '(' { }
    argList ')' ';'
      { }
  | RETURN ';'
      { }
  | RETURN expr ';'
      { }
  ;

// if部 → IF '(' 条件 ')' '{' 文リスト '}' |
//	   if部 ELSIF '(' 条件 ')' '{' 文リスト '}'
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
//     | ID | ID '[' 式 ']' | INUM | RNUM | ID '(' 実引数リスト ')'
// Yacc では、変数名と配列名を表す２つの ID は、非終端記号 vname で
// 置き換えられる。
expr
課題８で作成した expr の定義の２行目(ADDOP)から最後から２行目(RNUM)までを、ここにコピー(この行は削除する)
  | ID '(' 
      { }
    argList ')'
      { }
  ;

// stmt と expr の右辺中の 変数を表す ID を置き換えたもの
vname
課題８で作成した vname の定義の２行目(ID)を、ここにコピー(この行は削除する)
  ;

// 実引数リスト → ε | 実引数リスト’
argList
  : /* 空列 */ { $$ = NULL; }
  | argList2   { $$ = $1; }
  ;

// 実引数リスト’ → 式 | 実引数リスト’ ',' 式
argList2
  : expr              { $$ = new ArgList; $$->push_back($1); }
  | argList2 ',' expr { $$ = $1; $$->push_back($3); }
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
ここに課題８で作成した makeAssignTree の本体をコピー(この行は削除) 
}

static ExprTree *makeBinExprTree(CConst op, ExprTree *lexp, ExprTree *rexp)
{
ここに課題８で作成した makeBinExprTree の本体をコピー(この行は削除) 
}

static RelationTree *makeRelationTree(CConst op, ExprTree *e1, ExprTree *e2)
{
ここに課題８で作成した makeRelationTree の本体をコピー(この行は削除) 
}

static ExprTree *makeCallTree(string name, ArgList *args, ProcEntry *callee)
{

}

static LocalVarTree *initLocalVar(string name, Type vtype, ExprTree *expr)
{

}

static ReturnTree *makeDefaultReturnTree(Type type)
{
  ReturnTree *tree;
  int num = proc->getParamNumber();
  switch (type)  {
  case TInt:
    tree = new ReturnTree(new INumNode(0), num);
    break;
  case TReal:
    tree = new ReturnTree(new RNumNode(0), num);
    break;
  default:  // TVoid
    tree = new ReturnTree(NULL, num);
  }
  return tree;
}

static ReturnTree *makeReturnTreeWithValue(ExprTree *val)
{

}

static void addParameters(ParamList *params)
{

}

void usage(char *cmd)
{
  fprintf(stderr,"利用法: %s 原始プログラムファイル名\n",cmd);
  exit(2);
}

main(int argc, char **argv)
{
#if YYDEBUG
  extern int yydebug;

  yydebug = 1;	/* デバッグ表示付きの構文解析系を生成したいとき 1 を代入 */
#endif

  /* list が true なら，コンパイル後実行せず
     構文木から再現された原始プログラムを表示する */
  bool list = false;
  bool trace = false;
  char *cmd = *argv;	// コンパイラのコマンド名

  if (argc < 2)
    usage(cmd);

  /* 最初の引数がオプションか？ */
  while (**++argv == '-')  {
    argc--;
    switch (*(*argv+1))  {
    case 'l':
      if (!trace)
        list = true;
      break;
    case 't':
      if (!list)  {
        setTrace();
	trace = true;
      }
      break;
    case 's':
      setSpeed(atoi(*argv+2));
      break;
    default:
      printf("無効なオプション -%s\n",*argv);
    }
  }
  if (argc <= 0)
    usage(cmd);

#if YYDEBUG
  yydebug = 1;	/* デバッグ表示付きの構文解析系を生成したいとき 1 を代入 */
#endif

  setFileName(*argv);
  initializeScanner(*argv);
  initializeSymbolTable();
  addSystemProcedures();
  yyparse();
  if (list == 1)
    printCode(compiled);
  else
    interpret(compiled);
}
