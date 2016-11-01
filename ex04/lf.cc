#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lf-scanner.h"
#include "error.h"
#include "parse.h"

void usage(char *cmd);

main(int argc, char **argv)
{
  char *lf;

  // 引数が１つでなければ使用法を表示して終了
  if (argc != 2)  {
    usage(*argv);
  }
  lf = *++argv;
  setFileName(lf);		// エラー表示のためにファイル名を保存
  initializeScanner(lf);	// 字句解析系の初期化
  // 構文解析を行い，解析した論理式の論理値を表示する
  printf("logical value = %s\n",(parse() ? "true" : "false"));
}

// コマンドの使用法を表示して終了する
void usage(char *cmd)
{
  // cmd からパス名を除き，コマンド名だけにしたものを表示する
  char *p = strrchr(cmd,'/');	// 最後に現れる / を見つける
  /* 最後に現れる / 以降をコマンド名として表示する
     cmd 中に / がなければ，全体をコマンド名として表示する */
  fprintf(stderr,"usage: %s filename\n", (p ? p+1 : cmd));
  exit(1);
}
