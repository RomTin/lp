// symtable-test.cc で定義されている関数のプロトタイプ宣言

VarEntry *addVariableG(string name, VarClass vc, Type type,
                       bool array, int size, SymbolTable *table);
void addProcedure(string name, Type type);
SymbolEntry *findG(string name, SymbolTable *table);
void printAllSymbols();
void printSymbol(SymbolEntry *symbol);
