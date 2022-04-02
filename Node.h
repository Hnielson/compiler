#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include "Symbol.h"
#include "instructions/instructions.h"

// forward declarations
class Node;
class StartNode;
class ProgramNode;
class BlockNode;

class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class IdentifierNode;
class AssignmentStatementNode;
class ExpressionNode;
class CoutStatementNode;

class IntegerNode;
class BinaryOperatorNode;

class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;

class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;

class IfElseStatementNode;
class WhileStatementNode;

class LogicalAndNode;
class LogicalOrNode;
class BitwiseAndNode;


class Node {
public:
    virtual ~Node() = 0;
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass& machineCode) = 0;
};

class StartNode: public Node {
private:
    ProgramNode *mPN;
public:
    StartNode(ProgramNode *pn);
    ~StartNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ProgramNode: public Node {
private:
    BlockNode *mBN;
public:
    ProgramNode(BlockNode *bn);
    ~ProgramNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class StatementNode: public Node {
private:
public:
};

class BlockNode: public StatementNode {
private:
    StatementGroupNode *mSGN;
public:
    BlockNode(StatementGroupNode *sgn);
    ~BlockNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class StatementGroupNode: public Node {
private:
    std::vector<StatementNode*> mSN;
public:
    StatementGroupNode();
    ~StatementGroupNode();
    void AddStatement(StatementNode *sn);
    void Interpret();
    void Code(InstructionsClass& machineCode);
};



class DeclarationStatementNode: public StatementNode {
private:
    IdentifierNode *mIN;
    ExpressionNode *mEN;
public:
    DeclarationStatementNode(IdentifierNode *in, ExpressionNode *en);
    ~DeclarationStatementNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class AssignmentStatementNode: public StatementNode {
protected:
    IdentifierNode *mIN;
    ExpressionNode *mEN;
public:
    AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en);
    ~AssignmentStatementNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class CoutStatementNode: public StatementNode {
private:
    std::vector<ExpressionNode*> mEN;
public:
    CoutStatementNode();
    ~CoutStatementNode();
    void AddExpression(ExpressionNode* en);
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ExpressionNode {
public:
    virtual int Evaluate() = 0;
    virtual ~ExpressionNode() = 0;
    virtual void CodeEvaluate(InstructionsClass& machineCode) = 0;
};

class IntegerNode: public ExpressionNode {
private:
    int mInt;
public:
    IntegerNode(int i);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class IdentifierNode: public ExpressionNode {
private:
    std::string mLabel;
    SymbolTableClass *mSymbolTable;
public:
    IdentifierNode(std::string label, SymbolTableClass *table);
    ~IdentifierNode();
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class BinaryOperatorNode: public ExpressionNode {
protected:
    ExpressionNode *mExpL;
    ExpressionNode *mExpR;
public:
    BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
    ~BinaryOperatorNode();
};

class PlusNode: public BinaryOperatorNode {
public:
    PlusNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class MinusNode: public BinaryOperatorNode {
public:
    MinusNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class TimesNode: public BinaryOperatorNode {
public:
    TimesNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class DivideNode: public BinaryOperatorNode {
public:
    DivideNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class LessNode: public BinaryOperatorNode {
public:
    LessNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class LessEqualNode: public BinaryOperatorNode {
public:
    LessEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class GreaterNode: public BinaryOperatorNode {
public:
    GreaterNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class GreaterEqualNode: public BinaryOperatorNode {
public:
    GreaterEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class EqualNode: public BinaryOperatorNode {
public:
    EqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class NotEqualNode: public BinaryOperatorNode {
public:
    NotEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class IfElseStatementNode: public StatementNode {
private:
    ExpressionNode *mEN;
    StatementNode *mSN;
public:
    IfElseStatementNode(ExpressionNode *en, StatementNode *sn);
    ~IfElseStatementNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class WhileStatementNode: public StatementNode {
private:
    ExpressionNode *mEN;
    StatementNode *mSN;
public:
    WhileStatementNode(ExpressionNode *en, StatementNode *sn);
    ~WhileStatementNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class LogicalAndNode: public BinaryOperatorNode {
public:
    LogicalAndNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class LogicalOrNode: public BinaryOperatorNode {
public:
    LogicalOrNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class BitwiseAndNode: public BinaryOperatorNode {
public:
    BitwiseAndNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class PlusEqualNode : public AssignmentStatementNode {
private:
    
public:
    PlusEqualNode(IdentifierNode* in, ExpressionNode* en);
    void Interpret();
    void Code(InstructionsClass &machineCode);
};

class MinusEqualNode : public AssignmentStatementNode {
private:
    
public:
    MinusEqualNode(IdentifierNode* in, ExpressionNode* en);
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ShiftRightNode : public BinaryOperatorNode {
public:
    ShiftRightNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class TimesEqualNode : public AssignmentStatementNode {
private:

public:
    TimesEqualNode(IdentifierNode* in, ExpressionNode* en);
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class DoWhileStatementNode : public StatementNode {
private:
    ExpressionNode* mEN;
    StatementNode* mSN;
public:
    DoWhileStatementNode(ExpressionNode* en, StatementNode* sn);
    ~DoWhileStatementNode();
    void Interpret();
    void Code(InstructionsClass& machineCode);
};

#endif