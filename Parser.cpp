#include "Parser.h"

ParserClass::ParserClass(ScannerClass *scanner, SymbolTableClass *table)
    : mScanner(scanner), mSymbolTable(table) {
}

ParserClass::~ParserClass()
{
    /*delete mScanner;
    delete mSymbolTable;*/
}

TokenClass ParserClass::Match(TokenType expectedType)
{
    TokenClass currentToken = mScanner->GetNextToken();
    if(currentToken.GetTokenType() != expectedType)
    {
        cerr << "Error in ParserClass::Match" << endl;
        cerr << "Expected token type " <<
            TokenClass::GetTokenTypeName(expectedType) <<
            ", but got type " << currentToken.GetTokenTypeName()
            << endl;
        exit(1);
    }
    MSG("\tSuccessfully matched Token Type: " <<
        currentToken.GetTokenTypeName() << ", Lexeme: \"" <<
        currentToken.GetLexeme() << "\"");
    return currentToken;
}

StartNode * ParserClass::Start()
{
    ProgramNode *pn = Program();
    Match(ENDFILE_TOKEN); 
    return new StartNode(pn);
}

ProgramNode * ParserClass::Program()
{
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode * bn = Block();
    return new ProgramNode(bn);
}

BlockNode * ParserClass::Block()
{
    Match(LCURLY_TOKEN);
    StatementGroupNode * sgn = StatementGroup();
    Match(RCURLY_TOKEN);
    return new BlockNode(sgn);
}

StatementGroupNode * ParserClass::StatementGroup()
{
    StatementGroupNode * sgn = new StatementGroupNode();
    while(true)
    {
        StatementNode* sn = Statement();
        if (sn != NULL)
            sgn->AddStatement(sn);
        else
            break;
    }
    return sgn;
}

StatementNode * ParserClass::Statement()
{
    TokenClass tc = mScanner->PeekNextToken();
    TokenType tt = tc.GetTokenType();
    if(tt == INT_TOKEN)
    {
        return DeclarationStatement();
    }
    if(tt == IDENTIFIER_TOKEN)
    {
        return AssignmentStatement();
    }
    if(tt == COUT_TOKEN)
    {
        return CoutStatement();
    }
    if(tt == IF_TOKEN)
    {
        return IfStatement();
    }
    if(tt == WHILE_TOKEN)
    {
        return WhileStatement();
    }
    if(tt == LCURLY_TOKEN)
    {
        return Block();
    }
    if (tt == DO_TOKEN)
    {
        return DoWhileStatement();
    }
    return NULL;
}

// DeclarationStatement-> INT_TOKEN <Identifier> SEMICOLON_TOKEN
DeclarationStatementNode * ParserClass::DeclarationStatement()
{
    Match(INT_TOKEN);
    IdentifierNode * in = Identifier();
    if(mScanner->PeekNextToken().GetTokenType() == ASSIGNMENT_TOKEN)
    {
        Match(ASSIGNMENT_TOKEN);
        ExpressionNode * en = Expression();
        Match(SEMICOLON_TOKEN);
        return new DeclarationStatementNode(in, en);
    }
    Match(SEMICOLON_TOKEN);
    return new DeclarationStatementNode(in, NULL);
}

AssignmentStatementNode * ParserClass::AssignmentStatement()
{
    IdentifierNode * in = Identifier();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == ASSIGNMENT_TOKEN) {
        Match(ASSIGNMENT_TOKEN);
        ExpressionNode* en = Expression();
        Match(SEMICOLON_TOKEN);
        return new AssignmentStatementNode(in, en);
    }
    if (tt == PLUSEQUAL_TOKEN) {
        Match(PLUSEQUAL_TOKEN);
        ExpressionNode* en = Expression();
        Match(SEMICOLON_TOKEN);
        return new PlusEqualNode(in, en);
    }
    if (tt == MINUSEQUAL_TOKEN) {
        Match(MINUSEQUAL_TOKEN);
        ExpressionNode* en = Expression();
        Match(SEMICOLON_TOKEN);
        return new MinusEqualNode(in, en);
    }
    if (tt == TIMES_EQUAL_TOKEN) {
        Match(TIMES_EQUAL_TOKEN);
        ExpressionNode* en = Expression();
        Match(SEMICOLON_TOKEN);
        return new TimesEqualNode(in, en);
    }
}

CoutStatementNode * ParserClass::CoutStatement()
{
    CoutStatementNode* csn = new CoutStatementNode();
    Match(COUT_TOKEN);
    TokenType tt;
    do {
        Match(INSERTION_TOKEN);
        tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == ENDL_TOKEN) {
            Match(ENDL_TOKEN);
            csn->AddExpression(NULL);
        }
        else
            csn->AddExpression(Expression());
    } while (mScanner->PeekNextToken().GetTokenType() != SEMICOLON_TOKEN);
    Match(SEMICOLON_TOKEN);
    return csn;
}

IfElseStatementNode * ParserClass::IfStatement()
{
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * en = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * sn = Statement();
    return new IfElseStatementNode(en, sn);
}

WhileStatementNode * ParserClass::WhileStatement()
{
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * en = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * sn = Statement();
    return new WhileStatementNode(en, sn);
}

DoWhileStatementNode* ParserClass::DoWhileStatement()
{
    Match(DO_TOKEN);
    StatementNode* sn = Statement();
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RPAREN_TOKEN);
    Match(SEMICOLON_TOKEN);
    return new DoWhileStatementNode(en, sn);
}

ExpressionNode * ParserClass::Expression()
{
    return LogicalOr();
}

ExpressionNode * ParserClass::LogicalOr()
{
    ExpressionNode * current = LogicalAnd();

    while(true) {
        TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
        if(tt == LOGICAL_OR_TOKEN) {
            Match(tt);
            current = new LogicalOrNode(current, LogicalAnd());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::LogicalAnd()
{
    ExpressionNode * current = BitwiseAnd();

    while(true) {
        TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
        if(tt == LOGICAL_AND_TOKEN) {
            Match(tt);
            current = new LogicalAndNode(current, BitwiseAnd());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::BitwiseAnd()
{
    ExpressionNode * current = Relational();

    while(true) {
        TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
        if(tt == BITWISE_AND_TOKEN) {
            Match(tt);
            current = new BitwiseAndNode(current, Relational());
        } else {
            return current;
        }
    }
}


IdentifierNode * ParserClass::Identifier()
{
    TokenClass tc = Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(tc.GetLexeme(), mSymbolTable);
}

IntegerNode * ParserClass::Integer()
{
    TokenClass tc = Match(INTEGER_TOKEN);
    return new IntegerNode(atoi(tc.GetLexeme().c_str()));
}


ExpressionNode * ParserClass::Relational()
{
    ExpressionNode * current = ShiftRight();

    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == LESS_TOKEN)
    {
        Match(tt);
        current = new LessNode(current, ShiftRight());

    }
    else if(tt == LESSEQUAL_TOKEN)
    {
        Match(tt);
        current = new LessEqualNode(current, ShiftRight());
    }
    else if(tt == GREATER_TOKEN)
    {
        Match(tt);
        current = new GreaterNode(current, ShiftRight());
    }
    else if(tt == GREATEREQUAL_TOKEN)
    {
        Match(tt);
        current = new GreaterEqualNode(current, ShiftRight());
    }
    else if(tt == EQUAL_TOKEN)
    {
        Match(tt);
        current = new EqualNode(current, ShiftRight());
    }
    else if(tt == NOTEQUAL_TOKEN)
    {
        Match(tt);
        current = new NotEqualNode(current, ShiftRight());
    }
    return current;
}

ExpressionNode* ParserClass::ShiftRight()
{
    ExpressionNode* current = PlusMinus();

    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == SHIFT_RIGHT_TOKEN)
        {
            Match(SHIFT_RIGHT_TOKEN);
            current = new ShiftRightNode(current, PlusMinus());
        }
        return current;
    }
}

ExpressionNode * ParserClass::PlusMinus()
{
    ExpressionNode * current = TimesDivide();
    while(true)
    {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == PLUS_TOKEN)
        {
            Match(tt);
            current = new PlusNode(current, TimesDivide());
        }
        else if(tt == MINUS_TOKEN)
        {
            Match(tt);
            current = new MinusNode(current, TimesDivide());
        }
        else
        {
            return current;
        }
    }
}

ExpressionNode * ParserClass::TimesDivide()
{
    ExpressionNode * current = Factor();
    while (true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == TIMES_TOKEN)
        {
            Match(tt);
            current = new TimesNode(current, Factor());
        }
        else if(tt == DIVIDE_TOKEN)
        {
            Match(tt);
            current = new DivideNode(current, Factor());
        }
        else
        {
            return current;
        }
    }
}

ExpressionNode * ParserClass::Factor()
{
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == IDENTIFIER_TOKEN)
    {
        return Identifier();
    }
    else if(tt == INTEGER_TOKEN)
    {
        return Integer();
    }   
    else if (tt == TRUE_TOKEN)
    {
        Match(tt);
        return new IntegerNode(1);
    }
    else if (tt == FALSE_TOKEN)
    {
        Match(tt);
        return new IntegerNode(0);
    }
    else if(tt == LPAREN_TOKEN)
    {
        Match(tt);
        ExpressionNode * en = Expression();
        Match(RPAREN_TOKEN);
        return en;
    }
    else
    {
        cerr << "Identifier, Integer, or Lparen token not found" << endl;
        exit(1);
    }
}