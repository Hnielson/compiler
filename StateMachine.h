#ifndef STATE_MACHINE
#define STATE_MACHINE

#include "Token.h"
#include "Debug.h"

enum MachineState {
    START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
    EOF_STATE, LESS_STATE, LESSEQUAL_STATE, INSERTION_STATE,
    GREATER_STATE, GREATEREQUAL_STATE, EQUAL_STATE, NOT_STATE,
    NOTEQUAL_STATE, ASSIGNMENT_STATE, PLUS_STATE, MINUS_STATE,
    PLUSEQUAL_STATE, MINUSEQUAL_STATE, TIMES_STATE, DIVIDE_STATE,
    SEMICOLON_STATE, RPAREN_STATE, LPAREN_STATE, AMPERSAN_STATE,
    AND_STATE, OR_STATE, MOD_STATE, SHIFT_STATE, RCURLY_STATE,
    LCURLY_STATE, LINECOMMENT_STATE, BLOCKCOMMENT_STATE,
    BLOCKCOMMENT_END_STATE, BITWISE_AND_STATE, BITWISE_OR_STATE,
    LOGICAL_AND_STATE, LOGICAL_OR_STATE, PLUS_EQUAL_STATE,
    MINUS_EQUAL_STATE, SHIFT_RIGHT_STATE, TIMES_EQUAL_STATE,
    LAST_STATE
};

enum CharacterType {
    LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, BAD_CHAR,
    LESS_CHAR, LESSEQUAL_CHAR, INSERTION_CHAR, GREATER_CHAR,
    GREATEREQUAL_CHAR, AND_CHAR, OR_CHAR, NOT_CHAR,
    NOTEQUAL_CHAR, EQUAL_CHAR, MINUS_CHAR, TIMES_CHAR,
    DIVIDE_CHAR, SEMICOLON_CHAR, LINECOMMENT_CHAR, BLOCKCOMMENT_CHAR,
    NEWLINE_CHAR, RPAREN_CHAR, LPAREN_CHAR, RCURLY_CHAR,
    LCURLY_CHAR, EOF_CHAR, BITWISE_AND_CHAR, BITWISE_OR_CHAR,
    LAST_CHAR
};

class StateMachineClass
{
public:
    StateMachineClass();
    MachineState UpdateState(char currentCharacter, TokenType & 
        correspondingTokenType);
        
private:
    MachineState mCurrentState;

    // The matrix of legal moves:
    MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

    // Which end-machine-states correspond to which token types.
    // (non end states correspond to the BAD_TOKEN token type)
    TokenType mCorrespondingTokenTypes[LAST_STATE];
};

#endif // State Machine