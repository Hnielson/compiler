#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Symbol.h"
#include "Token.h"
#include "Node.h"

class ParserClass
{
private:
    ScannerClass *mScanner;
    SymbolTableClass *mSymbolTable;
public:
    ParserClass(ScannerClass *scanner, SymbolTableClass *table);
    ~ParserClass();
    TokenClass Match(TokenType expectedType);
    StartNode * Start();
    ProgramNode * Program();
    BlockNode * Block();
    StatementGroupNode * StatementGroup();
    StatementNode * Statement();
    DeclarationStatementNode * DeclarationStatement();
    AssignmentStatementNode* AssignmentStatement();
    CoutStatementNode * CoutStatement();
    IfElseStatementNode * IfStatement();
    WhileStatementNode * WhileStatement();
    DoWhileStatementNode* DoWhileStatement();
    ExpressionNode * LogicalAnd();
    ExpressionNode * LogicalOr();
    ExpressionNode * BitwiseAnd();
    ExpressionNode * Expression();
    IdentifierNode * Identifier();
    IntegerNode * Integer();
    ExpressionNode * Relational();
    ExpressionNode* ShiftRight();
    ExpressionNode * PlusMinus();
    ExpressionNode * TimesDivide();
    ExpressionNode * Factor();
};

#endif