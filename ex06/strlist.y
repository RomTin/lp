%{
using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．
  s1220091 国分佑太朗
  s1220228 海老原圭吾
  s1220233 小松凌也
  s1220244 向佐裕貴
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
%union {
  int num;
  string* str;
}


%token <str> STR
%token <num> NUM

%type <num> expr
%type <num> elem
%type <num> body
%type <num> body2

%left '+'
%left '*'

%%

// 規則部
// ここに翻訳規則を書く。 

// strlistの置き換え規則
// 配列の要素を出力したあとの改行と、その長さを出力する。
strlist : '[' body ']'  { printf("\n"); printf("The length of list is %d\n", $2); }

// bodyの置き換え規則
// $$に出力文字数を格納している。
body    : /*empty*/{ $$ = 0; }
        | body2 { $$ = $1; }

// elem について 
elem: STR  { 
    // 文字列が1つしか存在しない場合は，1件出力する
    printf("%s", $1->c_str()); 
    // 要素の数は1
    $$ = 1; 
    }
    | STR '!' expr { 
    // 文字列 ! 繰り返し数の場合
    // 繰り替えし数が0件以下の場合はエラーを出す
      if ($3 <= 0 ) {
        compileError(EIllegalExpValue, $3);
      }
      // 値を初期化する
      $$ = 0;
      // 文字列の後続にコンマを出力しなければならない $3-1件回だけ繰り返す
      for (int i = 0;  i < (int)$3-1 ; i++ ) {
        // 文字列 + コンマを出力する
        printf("%s,", $1->c_str());
        // 件数を数える
        $$ += 1;
        }
      // 最後の文字列出力だけは，コンマ不要
      printf("%s", $1->c_str());
      // 件数を数える
      $$ += 1;
      }
    ;

body2 : elem {$$=$1;}
     |body ',' {printf(",");} elem { $$=$1+$4; }//後続する要素があるときコンマを出力
     ;

expr : expr '+' expr { $$ = $1 + $3; }
     | expr '*' expr { $$ = $1 * $3; }
     | NUM { $$ = $1; }
     | '(' expr ')' { $$ = $2; }
     ;

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

