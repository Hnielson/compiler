#include "Token.h"

TokenClass::TokenClass()
{
}

TokenClass::~TokenClass()
{
}

TokenClass::TokenClass(TokenType type, const string & lexeme)
	: mType(type), mLexeme(lexeme)
{
}

TokenType TokenClass::GetTokenType() const
{
	return mType;
}

const string &TokenClass::GetTokenTypeName() const
{
	return gTokenTypeNames[mType];
}

string TokenClass::GetLexeme() const
{
	return mLexeme;
}

void TokenClass::CheckReserved()
{
	if (mLexeme == "void")
		mType = VOID_TOKEN;
	else if (mLexeme == "main")
		mType = MAIN_TOKEN;
	else if (mLexeme == "int")
		mType = INT_TOKEN;
	else if (mLexeme == "cout")
		mType = COUT_TOKEN;
	else if (mLexeme == "if")
		mType = IF_TOKEN;
	else if (mLexeme == "while")
		mType = WHILE_TOKEN;
	else if (mLexeme == "endl")
		mType = ENDL_TOKEN;
	else if (mLexeme == "true")
		mType = TRUE_TOKEN;
	else if (mLexeme == "false")
		mType = FALSE_TOKEN;
	else if (mLexeme == "and")
		mType = LOGICAL_AND_TOKEN;
	else if (mLexeme == "or")
		mType = LOGICAL_OR_TOKEN;
	else if (mLexeme == "do")
		mType = DO_TOKEN;
}

const string &TokenClass::GetTokenTypeName(TokenType type)
{
	return gTokenTypeNames[type];
}

ostream & operator<<(ostream & out, const TokenClass & tc)
{
	out.setf(ios::left);
	out << "Type: " << setw(15) << tc.GetTokenType() <<
		"TypeName: " << setw(15) << tc.GetTokenTypeName() <<
		"Lexeme: " << setw(15) << tc.GetLexeme();
	return out;
}
