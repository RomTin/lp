#ifndef __TGLC_CONST_H__
#define __TGLC_CONST_H__

using namespace std;

#include <string>
#include <vector>

// コンパイラで使う定数の定義

enum CConst { /* 最初の８つは文字コードをそのまま定数値に使う．
		 こうすることで読んだ文字をそのままyylval.op に
		 代入できるようになるので，yylex() 中の条件分岐を
		 簡略化できる */
	      Cadd = '+',		//  +
	      Csubtract = '-',		//  -
	      Cmultiply = '*',		//  *
	      Cmodulo = '%',		//  %
	      Cdivide = '/',		//  /
	      Cand = '&',		// &&
	      Cor = '|',		// ||
	      Cnot = '!',		// !
	      /* これ以降の定数値がこれ以前の定数値と衝突しないように、
	         CgreaterThanの値をどのASCII文字コードよりも大きい値に
		 しておく */
	      CgreaterThan = 128,	//  >
	      CgreaterThanOrEqual,	//  >=
	      ClessThan,		//  <
	      ClessThanOrEqual,		//  <=
	      Cequal,			//  ==
	      CnotEqual,		//  !=
	      Cint2real,		// 整数型から実数型への型変換
	      Creal2int			// 整数型から実数型への型変換
};

// 型  TVoid: void 型, TInt: int 型, TReal: real 型　
enum Type { TVoid, TInt, TReal };

// 引数の型のリスト
typedef vector<Type> TypeList;

#endif
