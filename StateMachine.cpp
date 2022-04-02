#include "StateMachine.h"

StateMachineClass::StateMachineClass()
// : mCurrentState(START_STATE)
{
    mCurrentState = START_STATE;
    // First, initialize all the mLegalMoves to CANTMOVE_STATE
    // Then, reset the mLegalMoves that are legitimate
    for (int i = 0; i < LAST_STATE; i++)
    {
        for (int j = 0; j < LAST_CHAR; j++)
        {
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }

    // Integer state
    mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;//
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;//

    // Identifier state
    mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;//
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;//
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;//

    // Less state
    mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;//
    // Less Equal state
    mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;//
    // Greater state
    mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;//
    // Greater Equal state
    mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;//

    mLegalMoves[START_STATE][EQUAL_CHAR] = ASSIGNMENT_STATE;//

    // Plus
    mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;//
    // Plus Equals
    mLegalMoves[PLUS_STATE][EQUAL_CHAR] = PLUS_EQUAL_STATE;
    // Minus
    mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;//
    // Minus Equals
    mLegalMoves[MINUS_STATE][EQUAL_CHAR] = MINUS_EQUAL_STATE;
    // Times
    mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;//
    // Times Equals
    mLegalMoves[TIMES_STATE][EQUAL_CHAR] = TIMES_EQUAL_STATE;
    // Divide
    mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;//

    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR] = EQUAL_STATE;//


    // Line Comments
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
    for (int i = 0; i < LAST_CHAR; i++)
    {
        mLegalMoves[LINECOMMENT_STATE][i] = LINECOMMENT_STATE;
    }
    mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;
    mLegalMoves[LINECOMMENT_STATE][EOF_CHAR] = EOF_STATE;

    // Block Comments
    mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENT_STATE;
    for (int i = 0; i < LAST_CHAR; i++)
    {
        mLegalMoves[BLOCKCOMMENT_STATE][i] = BLOCKCOMMENT_STATE;
    }
    mLegalMoves[BLOCKCOMMENT_STATE][TIMES_CHAR] = BLOCKCOMMENT_END_STATE;
    for (int i = 0; i < LAST_CHAR; i++)
    {
        mLegalMoves[BLOCKCOMMENT_END_STATE][i] = BLOCKCOMMENT_STATE;
    }
    mLegalMoves[BLOCKCOMMENT_END_STATE][TIMES_CHAR] = BLOCKCOMMENT_END_STATE;
    mLegalMoves[BLOCKCOMMENT_END_STATE][DIVIDE_CHAR] = START_STATE;

    // Parens & Curly Brackets
    mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;//
    mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;//
    mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;//
    mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;//

    // Semicolon
    mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;//

    // Insertion
    mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;//
    mLegalMoves[START_STATE][NOT_CHAR] = NOT_STATE;//
    mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;//

    // EOF
    mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE;

    // Whitespace state
    mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;//
    mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;//

    // BITWISE AND & OR
    mLegalMoves[START_STATE][BITWISE_AND_CHAR] = BITWISE_AND_STATE;
    mLegalMoves[BITWISE_AND_STATE][BITWISE_AND_CHAR] = LOGICAL_AND_STATE;
    mLegalMoves[START_STATE][BITWISE_OR_CHAR] = BITWISE_OR_STATE;
    mLegalMoves[BITWISE_OR_STATE][BITWISE_OR_CHAR] = LOGICAL_OR_STATE;

    mLegalMoves[GREATER_STATE][GREATER_CHAR] = SHIFT_RIGHT_STATE;


    // First, initialize all states to correspond to the BAD token type.
    // Then, reset the end states to correspond to the correct token type.
    for(int i=0; i<LAST_STATE; i++)
    {
        mCorrespondingTokenTypes[i]= BAD_TOKEN;
    }
    mCorrespondingTokenTypes[LESS_STATE]= LESS_TOKEN;//
    mCorrespondingTokenTypes[LESSEQUAL_STATE]= LESSEQUAL_TOKEN;//
    mCorrespondingTokenTypes[GREATER_STATE]= GREATER_TOKEN;//
    mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;//
    mCorrespondingTokenTypes[EQUAL_STATE]= EQUAL_TOKEN;//
    mCorrespondingTokenTypes[NOTEQUAL_STATE]= NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE]= INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE]= ASSIGNMENT_TOKEN;//
    mCorrespondingTokenTypes[PLUS_STATE]= PLUS_TOKEN;//
    mCorrespondingTokenTypes[MINUS_STATE]= MINUS_TOKEN;//
    mCorrespondingTokenTypes[TIMES_STATE]= TIMES_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE]= DIVIDE_TOKEN;//
    mCorrespondingTokenTypes[SEMICOLON_STATE]= SEMICOLON_TOKEN;//
    mCorrespondingTokenTypes[LPAREN_STATE]= LPAREN_TOKEN;//
    mCorrespondingTokenTypes[RPAREN_STATE]= RPAREN_TOKEN;//
    mCorrespondingTokenTypes[LCURLY_STATE]= LCURLY_TOKEN;//
    mCorrespondingTokenTypes[RCURLY_STATE]= RCURLY_TOKEN;//
    mCorrespondingTokenTypes[IDENTIFIER_STATE]= IDENTIFIER_TOKEN;//
    mCorrespondingTokenTypes[INTEGER_STATE]= INTEGER_TOKEN;//
    mCorrespondingTokenTypes[EOF_STATE]= ENDFILE_TOKEN;//
    mCorrespondingTokenTypes[LOGICAL_AND_STATE]= LOGICAL_AND_TOKEN;
    mCorrespondingTokenTypes[LOGICAL_OR_STATE]= LOGICAL_OR_TOKEN;
    mCorrespondingTokenTypes[BITWISE_AND_STATE]= BITWISE_AND_TOKEN;
    mCorrespondingTokenTypes[PLUS_EQUAL_STATE] = PLUSEQUAL_TOKEN;
    mCorrespondingTokenTypes[MINUS_EQUAL_STATE] = MINUSEQUAL_TOKEN;
    mCorrespondingTokenTypes[SHIFT_RIGHT_STATE] = SHIFT_RIGHT_TOKEN;
    mCorrespondingTokenTypes[TIMES_EQUAL_STATE] = TIMES_EQUAL_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter,
    TokenType & correspondingTokenType)
{
    CharacterType chartype = BAD_CHAR;//
    if(currentCharacter == EOF)//
        chartype = EOF_CHAR;
    if(isspace(currentCharacter))//
        chartype = WHITESPACE_CHAR;
    if(currentCharacter == '+')//
        chartype = PLUS_CHAR;
    if(currentCharacter == '-')//
        chartype = MINUS_CHAR;
    if(currentCharacter == '*')//
        chartype = TIMES_CHAR;
    if(currentCharacter == '/')//
        chartype = DIVIDE_CHAR;
    if(isdigit(currentCharacter))//
        chartype = DIGIT_CHAR;
    if(currentCharacter == '\n')//
        chartype = NEWLINE_CHAR;
    if(currentCharacter == '<')//
        chartype = LESS_CHAR;
    if(currentCharacter == '>')//
        chartype = GREATER_CHAR;
    if(isalpha(currentCharacter))//
        chartype = LETTER_CHAR;
    if(currentCharacter == '!')//
        chartype = NOT_CHAR;
    if(currentCharacter == '=')
        chartype = EQUAL_CHAR;
    if(currentCharacter == ';')//
        chartype = SEMICOLON_CHAR;
    if(currentCharacter == '(')//
        chartype = LPAREN_CHAR;
    if(currentCharacter == ')')//
        chartype = RPAREN_CHAR;
    if(currentCharacter == '{')//
        chartype = LCURLY_CHAR;
    if(currentCharacter == '}')//
        chartype = RCURLY_CHAR;
    if(currentCharacter == '&')
        chartype = BITWISE_AND_CHAR;
    if(currentCharacter == '|')
        chartype = BITWISE_OR_CHAR;


    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][chartype];
    return mCurrentState;
}