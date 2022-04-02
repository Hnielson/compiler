#include "Node.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode *pn)
    : mPN(pn) {}
StartNode::~StartNode() {delete mPN;}
void StartNode::Interpret()
{
    mPN->Interpret();
}
void StartNode::Code(InstructionsClass& machineCode)
{
    mPN->Code(machineCode);
}

ProgramNode::ProgramNode(BlockNode *bn)
    : mBN(bn) {}
ProgramNode::~ProgramNode() {delete mBN;}
void ProgramNode::Interpret()
{
    mBN->Interpret();
}
void ProgramNode::Code(InstructionsClass& machineCode)
{
    mBN->Code(machineCode);
}

BlockNode::BlockNode(StatementGroupNode *sgn)
    : mSGN(sgn) {}
BlockNode::~BlockNode() {delete mSGN;}
void BlockNode::Interpret()
{
    mSGN->Interpret();
}
void BlockNode::Code(InstructionsClass& machineCode)
{
    mSGN->Code(machineCode);
}

StatementGroupNode::StatementGroupNode()
    : mSN(std::vector<StatementNode*>{}) {}
StatementGroupNode::~StatementGroupNode()
{
    for(auto i: mSN)
        delete i;
}
void StatementGroupNode::AddStatement(StatementNode *sn)
{
    mSN.push_back(sn);
}
void StatementGroupNode::Interpret()
{
    for(auto i: mSN)
        i->Interpret();
}
void StatementGroupNode::Code(InstructionsClass& machineCode)
{
    for (auto i : mSN)
        i->Code(machineCode);
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *in, ExpressionNode *en)
    : mIN(in), mEN(en) {}
DeclarationStatementNode::~DeclarationStatementNode() {delete mIN; delete mEN;}
void DeclarationStatementNode::Interpret()
{
    mIN->DeclareVariable();
    if(mEN != NULL) {
        mIN->SetValue(mEN->Evaluate());
    }
}
void DeclarationStatementNode::Code(InstructionsClass& machineCode)
{
    mIN->DeclareVariable();
    if (mEN != NULL) {
        mEN->CodeEvaluate(machineCode);
        int index = mIN->GetIndex();
        machineCode.PopAndStore(index);
    }
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en)
    : mIN(in), mEN(en) {}
AssignmentStatementNode::~AssignmentStatementNode() {delete mIN; delete mEN;}
void AssignmentStatementNode::Interpret()
{
    mIN->SetValue(mEN->Evaluate());
}
void AssignmentStatementNode::Code(InstructionsClass& machineCode)
{
    mEN->CodeEvaluate(machineCode);
    int index = mIN->GetIndex();
    machineCode.PopAndStore(index);
}

CoutStatementNode::CoutStatementNode()
    : mEN(std::vector<ExpressionNode*>{}) {}
CoutStatementNode::~CoutStatementNode()
{
    for(auto i : mEN)
        delete i;
}
void CoutStatementNode::AddExpression(ExpressionNode* en)
{
    mEN.push_back(en);
}
void CoutStatementNode::Interpret()
{
    for (int i = 0; i < mEN.size(); i++) {
        if (mEN[i] != NULL)
            cout << mEN[i]->Evaluate();
        else
            cout << endl;
    }
}
void CoutStatementNode::Code(InstructionsClass& machineCode)
{
    for (int i = 0; i < mEN.size(); i++) {
        if (mEN[i] != NULL) {
            mEN[i]->CodeEvaluate(machineCode);
            machineCode.PopAndWrite();
        }
        else
            machineCode.WriteEndl();
    }
}

ExpressionNode::~ExpressionNode() {}

IntegerNode::IntegerNode(int i)
    : mInt(i) {}
int IntegerNode::Evaluate()
{
    return mInt;
}
void IntegerNode::CodeEvaluate(InstructionsClass& machineCode)
{
    machineCode.PushValue(Evaluate());
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* table)
    : mLabel(label), mSymbolTable(table) {}
IdentifierNode::~IdentifierNode() {}
void IdentifierNode::DeclareVariable() 
{
    mSymbolTable->AddEntry(mLabel);
}
void IdentifierNode::SetValue(int v) 
{
    mSymbolTable->SetValue(mLabel, v);
}
int IdentifierNode::GetIndex() 
{
    return mSymbolTable->GetIndex(mLabel);
}
int IdentifierNode::Evaluate() 
{
    return mSymbolTable->GetValue(mLabel);
}
void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode)
{
    machineCode.PushVariable(GetIndex());
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right)
    : mExpL(left), mExpR(right) {}
BinaryOperatorNode::~BinaryOperatorNode() {delete mExpL; delete mExpR;}

PlusNode::PlusNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int PlusNode::Evaluate()
{
    return mExpL->Evaluate() + mExpR->Evaluate();
}
void PlusNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int MinusNode::Evaluate()
{
    return mExpL->Evaluate() - mExpR->Evaluate();
}
void MinusNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int TimesNode::Evaluate()
{
    return mExpL->Evaluate() * mExpR->Evaluate();
}
void TimesNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int DivideNode::Evaluate()
{
    return mExpL->Evaluate() / mExpR->Evaluate();
}
void DivideNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

LessNode::LessNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int LessNode::Evaluate()
{
    return mExpL->Evaluate() < mExpR->Evaluate();
}
void LessNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int LessEqualNode::Evaluate()
{
    return mExpL->Evaluate() <= mExpR->Evaluate();
}
void LessEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int GreaterNode::Evaluate()
{
    return mExpL->Evaluate() > mExpR->Evaluate();
}
void GreaterNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int GreaterEqualNode::Evaluate()
{
    return mExpL->Evaluate() >= mExpR->Evaluate();
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int EqualNode::Evaluate()
{
    return mExpL->Evaluate() == mExpR->Evaluate();
}
void EqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode *left, ExpressionNode *right) 
    : BinaryOperatorNode(left, right) {}
int NotEqualNode::Evaluate()
{
    return mExpL->Evaluate() != mExpR->Evaluate();
}
void NotEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
}

IfElseStatementNode::IfElseStatementNode(ExpressionNode *en, StatementNode *sn)
    : mEN(en), mSN(sn) {}
IfElseStatementNode::~IfElseStatementNode() {delete mEN; delete mSN;}
void IfElseStatementNode::Interpret()
{
    if(mEN->Evaluate())
    {
        mSN->Interpret();
    }
}
void IfElseStatementNode::Code(InstructionsClass& machineCode)
{
    mEN->CodeEvaluate(machineCode);
    unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char* address1 = machineCode.GetAddress();
    mSN->Code(machineCode);
    unsigned char* address2 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
}
// void IfElseStatementNode::Code(InstructionsClass &machineCode)
// {
//     mExpression->CodeEvaluate(machineCode);
// }

WhileStatementNode::WhileStatementNode(ExpressionNode *en, StatementNode *sn)
    : mEN(en), mSN(sn) {}
WhileStatementNode::~WhileStatementNode() {}
void WhileStatementNode::Interpret()
{
    while(mEN->Evaluate())
    {
        mSN->Interpret();
    }
}
void WhileStatementNode::Code(InstructionsClass& machineCode)
{
    unsigned char* address1 = machineCode.GetAddress();
    mEN->CodeEvaluate(machineCode);
    unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char* address2 = machineCode.GetAddress();
    mSN->Code(machineCode);
    unsigned char* JumpAddress = machineCode.Jump();
    unsigned char* address3 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress, (int)(address3 - address2));
    machineCode.SetOffset(JumpAddress, (int)(address1 - address3));
}

LogicalAndNode::LogicalAndNode(ExpressionNode *left, ExpressionNode *right)
    : BinaryOperatorNode(left, right) {}
int LogicalAndNode::Evaluate()
{
    return (mExpL->Evaluate() && mExpR->Evaluate());
}
void LogicalAndNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

LogicalOrNode::LogicalOrNode(ExpressionNode *left, ExpressionNode *right)
    : BinaryOperatorNode(left, right) {}
int LogicalOrNode::Evaluate()
{
    return (mExpL->Evaluate() || mExpR->Evaluate());
}
void LogicalOrNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}

BitwiseAndNode::BitwiseAndNode(ExpressionNode *left, ExpressionNode *right)
    : BinaryOperatorNode(left, right) {}
int BitwiseAndNode::Evaluate()
{
    return (mExpL->Evaluate() & mExpR->Evaluate());
}
void BitwiseAndNode::CodeEvaluate(InstructionsClass& machineCode)
{
}

PlusEqualNode::PlusEqualNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
void PlusEqualNode::Interpret()
{
    int val = mIN->Evaluate() + mEN->Evaluate();
    mIN->SetValue(val);
}
void PlusEqualNode::Code(InstructionsClass &machineCode)
{
    machineCode.PushVariable(mIN->GetIndex());
    mEN->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
    machineCode.PopAndStore(mIN->GetIndex());
}

MinusEqualNode::MinusEqualNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
void MinusEqualNode::Interpret()
{
    int val = mIN->Evaluate() - mEN->Evaluate();
    mIN->SetValue(val);
}
void MinusEqualNode::Code(InstructionsClass& machineCode)
{
    machineCode.PushVariable(mIN->GetIndex());
    mEN->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
    machineCode.PopAndStore(mIN->GetIndex());
}

ShiftRightNode::ShiftRightNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int ShiftRightNode::Evaluate()
{
    return mExpL->Evaluate() >> mExpR->Evaluate();
}
void ShiftRightNode::CodeEvaluate(InstructionsClass& machineCode)
{
    mExpL->CodeEvaluate(machineCode);
    mExpR->CodeEvaluate(machineCode);
    machineCode.PopPopShiftRightPush();
}

TimesEqualNode::TimesEqualNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
void TimesEqualNode::Interpret()
{
    int val = mIN->Evaluate() * mEN->Evaluate();
    mIN->SetValue(val);
}
void TimesEqualNode::Code(InstructionsClass& machineCode)
{
    machineCode.PushVariable(mIN->GetIndex());
    mEN->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
    machineCode.PopAndStore(mIN->GetIndex());
}

DoWhileStatementNode::DoWhileStatementNode(ExpressionNode* en, StatementNode* sn)
    : mEN(en), mSN(sn) {}
DoWhileStatementNode::~DoWhileStatementNode() {}
void DoWhileStatementNode::Interpret()
{
    do {
        mSN->Interpret();
    } while (mEN->Evaluate());
}
void DoWhileStatementNode::Code(InstructionsClass& machineCode)
{
    unsigned char* a1 = machineCode.GetAddress();
    mSN->Code(machineCode);
    mEN->CodeEvaluate(machineCode);
    unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char* a2 = machineCode.GetAddress();
    unsigned char* JumpAddress = machineCode.Jump();
    unsigned char* a3 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress, (int)(a3 - a2));
    machineCode.SetOffset(JumpAddress, (int)(a1 - a3));
}
