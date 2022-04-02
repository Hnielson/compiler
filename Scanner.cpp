#include "Scanner.h"

ScannerClass::ScannerClass(string inputFilename)
{
    MSG("Initializing ScannerClass object");
    mFin.open(inputFilename.c_str(), ios::binary);
    if(!mFin.is_open())
    {
        cerr << "File open error" << endl;
        exit(EXIT_FAILURE);
    }
}

ScannerClass::~ScannerClass()
{
    mFin.close();
}

TokenClass ScannerClass::GetNextToken()
{
    StateMachineClass stateMachine;
    MachineState state;
    TokenType type;
    string lexeme;
    char c;
    do {
        // get next character
        c = mFin.get();
        if(c == '\n'){
            mLinenum++;
            col = 0;
        }
        if(c == '\t')
            col += 4;
        lexeme += c;
        col++;
        state = stateMachine.UpdateState(c, type);
        if(state == START_STATE || state == EOF_STATE)
            lexeme = "";
    } while (state != CANTMOVE_STATE);

    // Put back last token read
    mFin.unget();
    lexeme.pop_back();
    col--;

    if(c == '\n')
        mLinenum--;

    if(type == BAD_TOKEN)
    {
        cout << "Bad token parsed:[" << c << "] in lexeme:[" << lexeme << "]" << " at line number: " << mLinenum << " column: " << col << endl;
        exit(EXIT_FAILURE);
    }

    TokenClass token(type, lexeme);
    token.CheckReserved();
    return token;
}

TokenClass ScannerClass::PeekNextToken()
{
    int currentLine = mLinenum;
    streampos p = mFin.tellg();
    TokenClass t = GetNextToken();
    if(!mFin)
        mFin.clear();
    mFin.seekg(p);
    mLinenum = currentLine;
    return t;
}

int ScannerClass::GetLineNumber()
{
    return mLinenum;
}