#ifndef SCANNER
#define SCANNER

#include <fstream>
#include "StateMachine.h"
#include "Debug.h"

using namespace std;

class ScannerClass
{
private:
    ifstream mFin;
    int mLinenum = 1;
    int col = 0;
public:
    ScannerClass(string inputFilename);
    ~ScannerClass();
    TokenClass GetNextToken();
    TokenClass PeekNextToken();
    int GetLineNumber();
};


#endif // Scanner