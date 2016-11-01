%{
using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．

*******************************************************************/

// 宣言部

#include <string>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "error.h"

// yyparse() 内だけで有効な関数のプロトタイプ宣言

static int yyerror(const char *msg);	// yyparse()が用いるエラー処理関数
static void usage(char *cmd);		// 使用法の表示
%}

// ここに属性、トークン、非終端記号の宣言と、トークンの優先順位と結合性の宣言を書く



%%

// 規則部
// ここに翻訳規則を書く。

%%

// サブルーチン部
// サブルーチン部には追加・変更しない。


// yyparse()が用いるエラー処理用関数
static int yyerror(const char *msg)
{
  compileError(EParseError);
}


// メイン関数
main(int argc, char **argv)
{
#if YYDEBUG
  extern int yydebug;
  yydebug = 1;
#endif

  // 引数が１つでなければ使用法を表示して終了
  if (argc != 2)  {
    usage(*argv);
  }
  initializeScanner(*++argv);	// ファイル名を引数として字句解析系を初期化

  // 構文解析を行い，結果を表示する．結果の表示はyyparse()の中で行う．
  yyparse();
}

// コマンドの使用法を表示して終了する関数
void usage(char *cmd)
{
  // cmd からパス名を除き，コマンド名だけにしたものを表示する
  char *p = strrchr(cmd,'/');	// 最後に現れる / を見つける

  /* 最後に現れる / 以降をコマンド名として表示する
     cmd 中に / がなければ，全体をコマンド名として表示する */
  fprintf(stderr,"usage: %s filename\n", (p ? p+1 : cmd));
  exit(1);
}

