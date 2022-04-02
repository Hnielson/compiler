#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <iomanip>
#include "Debug.h"

using namespace std;

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, TRUE_TOKEN, FALSE_TOKEN,
	//Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
	TIMES_TOKEN, DIVIDE_TOKEN, LOGICAL_AND_TOKEN, LOGICAL_OR_TOKEN,
	PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN, SHIFT_RIGHT_TOKEN, TIMES_EQUAL_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
	RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN,
	BAD_TOKEN, ENDFILE_TOKEN, IF_TOKEN, WHILE_TOKEN, BITWISE_AND_TOKEN, DO_TOKEN,
	ELSE_TOKEN, ENDL_TOKEN
	};

const string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "TRUE", "FALSE",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL",
	"NOTEQUAL",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
	"LOGICALAND", "LOGICALOR", "PLUSEQUAL", "MINUSEQUAL", "SHIFTRIGHT", "TIMESEQUAL",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IDENTIFIER", "INTEGER",
	"BAD", "ENDFILE", "IF", "WHILE", "BITWISEAND", "DO", "ELSE", "ENDL"
	};

class TokenClass
{
private:
	TokenType mType;
	string mLexeme;
public:
	TokenClass();
	~TokenClass();
	TokenClass(TokenType type, const string & lexeme);
	TokenType GetTokenType() const;
	const string & GetTokenTypeName() const;
	string GetLexeme() const;
	void CheckReserved();
	static const string & GetTokenTypeName (TokenType type);
};


ostream & operator<<(ostream & out, const TokenClass & tc);

#endif // TOKEN
