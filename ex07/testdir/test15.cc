/****************************************************************************
  テスト１５： addGlobalVariable(), addLocalVariable(), 
               addParameter(), addArray(), findVariable() の返り値のテスト
  (1) addGlobalVariable(), addLocalVariable(), addParameter(),
      addArray() を呼び出して、globalSymTable や localSymTable に
      変数エントリを登録する。返り値は保存しておき、後でチェックする。
  (2) findVariable() を呼び出し、その返り値と上で保存した返り値が
      一致するかどうか調べる。

****************************************************************************/

using namespace std;

#include <map>
#include <stdio.h>
#include "symtable.h"
#include "const.h"
#include "symtable-test.h"


static void compareResult(VarEntry *var, VarEntry *found, string name);


main()
{
  VarEntry *var1, *var2, *var3, *var4, *var5;

  // 記号表への変数エントリを登録し，その返り値をvar1〜var5に保存する
  var1 = addLocalVariable("aVariable1",TInt);
  var2 = addGlobalVariable("aVariable2",TReal);
  var3 = addParameter("aVariable3",TInt);
  var4 = addArray("aVariable4",TInt,1);
  var5 = addLocalVariable("aVariable5",TReal);

  // 上で保存した返り値と findVariable() の返り値が一致することを
  // 確かめる．
  compareResult(var1,findVariable("aVariable1"),"aVariable1");
  compareResult(var2,findVariable("aVariable2"),"aVariable2");
  compareResult(var3,findVariable("aVariable3"),"aVariable3");
  compareResult(var4,findVariable("aVariable4"),"aVariable4");
  compareResult(var5,findVariable("aVariable5"),"aVariable5");
}


static void compareResult(VarEntry *var, VarEntry *found, string name)
{
  if (var == found)
    printf("変数%sのfindVariable()の返り値は正常\n",name.c_str());
  else
    printf("変数%sのfindVariable()の返り値が正しくない\n",name.c_str());
}
