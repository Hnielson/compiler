#ifndef SYMBOL
#define SYMBOL

#include <functional>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class SymbolTableClass
{
private:
    struct Variable {
        string mLabel;
        int mValue;
    };

    vector<Variable> table;
public:
    SymbolTableClass();
    ~SymbolTableClass();
        // returns true if <s> is already in the symbol table.
    bool Exists(const string & s);
        // adds <s> to the symbol table,
        // or quits if it was already there
    void AddEntry(const string & s);
        // returns the current value of variable <s>, when
        // interpreting. Meaningless for Coding and Executing.
        // Prints a message and quits if variable s does not exist.
    int GetValue(const string & s);
        // sets variable <s> to the given value, when interpreting.
        // Meaningless for Coding and Executing.
        // Prints a message and quits if variable s does not exist.
    void SetValue(const string & s, int v);
        // returns the index of where variable <s> is.
        // returns -1 if variable <s> is not there.
    int GetIndex(const string & s);
        // returns the current number of variables in the symbol
        // table.
    int GetCount();
};

#endif // Symbol