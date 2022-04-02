#include "Symbol.h"

SymbolTableClass::SymbolTableClass()
    : table(vector<Variable>{})
{
}

SymbolTableClass::~SymbolTableClass()
{
}

bool SymbolTableClass::Exists(const string & s)
{
    for(unsigned int i=0; i<table.size(); i++) {
        if(table[i].mLabel == s)
            return true;
    }
    return false;
}

void SymbolTableClass::AddEntry(const string & s)
{
    if(Exists(s)) {
        cout << "Entry already exists" << endl;
        exit(EXIT_FAILURE);
    }
    else
        table.push_back(Variable{s, 0});
}

int SymbolTableClass::GetValue(const string & s)
{
    int i = GetIndex(s);
    if(i != -1)
        return table[i].mValue;
    else {
        cout << "Value not found" << endl;
        exit(EXIT_FAILURE);
    }
}

void SymbolTableClass::SetValue(const string & s, int v)
{
    int i = GetIndex(s);
    if(i != -1)
        table[i].mValue = v;
    else {
        cout << "Variable does not exist" << endl;
        exit(EXIT_FAILURE);
    }
}

int SymbolTableClass::GetIndex(const string & s)
{
    for(unsigned int i=0; i<table.size(); i++) {
        if(table[i].mLabel == s)
            return i;
    }
    return -1;
}

int SymbolTableClass::GetCount()
{
    return table.size();
}