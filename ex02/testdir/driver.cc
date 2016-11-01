using namespace std;

#include <string>
#include <stdio.h>
#include <stdlib.h>
//#include "token.h"
#include "scanner.h"
#include "error.h"
#include "y.tab.h"
#include "data.h"


YYSTYPE yylval;

void makeTestFile(const char *name);
void tokenMismatch(int i, int token);
static const char *getOperatorString(int op);
static const char *getTokenName(int id);


main()
{
  int token, i, id, inum, rnum, op;

  id = inum = rnum = op = 0;

  makeTestFile("tmp.in");
  initializeScanner((char *)"tmp.in");
  for (i=0; i<NumOfTokens; i++)  {
    // テスト項目を出力
    fprintf(stderr,"%d: %s",i+1,getTokenName(tokens[i]));
    switch (tokens[i])  {
    case ID:
      fprintf(stderr," (%s) ",ids[id]);
      break;
    case INUM:
      fprintf(stderr," (%d) ",inums[inum]);
      break;
    case RNUM:
      fprintf(stderr," (%lf) ",rnums[rnum]);
      break;
    case ADDOP:
    case MULOP:
    case LOGOP:
    case ULOGOP:
    case RELOP:
      fprintf(stderr," (%s) ",getOperatorString(ops[op]));
    }
    fprintf(stderr,"を読む\n");
    // 字句解析系からトークンを取り出す
    token = yylex();
    fprintf(stderr,"     %sを読んだ\n",getTokenName(token));
    if (token != tokens[i])  {
      // トークンの種類自体が異なるなら、実際に読んだトークンと属性を出力
      tokenMismatch(i,token);
    }
    // トークンの種類は同じだった。
    // 属性も同じかどうかチェック
    switch (token)  {
    case ID:
      if (*yylval.symbol != ids[id])  {
        fprintf(stderr,"scanner.ccのエラー: 字句が%sではなく%sだった！\n",
                ids[id],yylval.symbol->c_str());
        exit(2);
      }
      id++;
      break;
    case INUM:
      if (yylval.inum != inums[inum])  {
        fprintf(stderr,"scanner.ccのエラー: 整数が%dでなく%dだった！\n",
                inums[inum],yylval.inum);
        exit(2);
      }
      inum++;
      break;
    case RNUM:
      if (yylval.rnum != rnums[rnum])  {
        fprintf(stderr,"scanner.ccのエラー: 実数が%lfでなく%lfだった！\n",
                rnums[rnum],yylval.rnum);
        exit(2);
      }
      rnum++;
      break;
    case ADDOP:
    case MULOP:
    case LOGOP:
    case ULOGOP:
    case RELOP:
      if (yylval.op != ops[op])  {
        fprintf(stderr,"scanner.ccのエラー: 演算子が%s でなく %s だった！\n",
                getOperatorString(ops[op]),getOperatorString(yylval.op));
        exit(2);
      }
      op++;
    }
    fprintf(stderr,"OK\n");
  }
  exit(0);
}

void makeTestFile(const char *name)
{
  FILE *fp;

  setFileName((char *)name);// エラーメッセージのために，ファイル名をセット

  if ((fp=fopen(name,"w")) == NULL)  {
    fprintf(stderr,"内部エラー: ファイル%sが開けません\n",name);
    exit(2);
  }
  unsigned char *p = buffer;
  while (*p != '\0')  {
    fputc(*p++,fp);
  }
  fclose(fp);
}

void tokenMismatch(int i, int token)
{
  fprintf(stderr,"scanner.ccのエラー: %sではなく%s ",
          getTokenName(tokens[i]),getTokenName(token));
  switch (token)  {
  case ID:
    fprintf(stderr,"(%s)",yylval.symbol);
    break;
  case INUM:
    fprintf(stderr,"(%d)",yylval.inum);
    break;
  case RNUM:
    fprintf(stderr,"(%lf)",yylval.rnum);
    break;
  case ADDOP:
  case MULOP:
  case RELOP:
  case LOGOP:
  case ULOGOP:
    fprintf(stderr,"(%s)",getOperatorString(yylval.op));
  }
  fprintf(stderr," を読んだ！\n");
  exit(2);
}

static const char *getOperatorString(int op)
{
  switch (op)  {
  case Cadd:
    return "+";
  case Csubtract:
    return "-";
  case Cmultiply:
    return "*";
  case Cdivide:
    return "/";
  case Cmodulo:
    return "%";
  case Cequal:
    return "==";
  case CnotEqual:
    return "!=";
  case CgreaterThan:
    return ">";
  case CgreaterThanOrEqual:
    return ">=";
  case ClessThan:
    return "<";
  case ClessThanOrEqual:
    return "<=";
  case Cand:
    return "&&";
  case Cor:
    return "||";
  case Cnot:
    return "!";
  }
}

static const char *getTokenName(int id)
{
  static char s[2];

  switch (id) {
  case ID:	return "ID";
  case INUM:	return "INUM";
  case RNUM:	return "RNUM";
  case ADDOP:	return "ADDOP";
  case MULOP:	return "MULOP";
  case LOGOP:	return "LOGOP";
  case ULOGOP:	return "ULOGOP";
  case RELOP:	return "RELOP";
  case VOID:	return "VOID";
  case INT:	return "INT";
  case REAL:	return "REAL";
  case IF:	return "IF";
  case ELSIF:	return "ELSIF";
  case ELSE:	return "ELSE";
  case WHILE:	return "WHILE";
  case REPEAT:	return "REPEAT";
  case RETURN:	return "RETURN";
  case EOF:     return "EOF";
  default:	s[0] = id; s[1] = '\0'; return s;
  }
}

