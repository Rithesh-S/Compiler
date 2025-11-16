#pragma once

enum class TokenType {
    //Literals
    NUMBER,
    IDENTIFIER,

    //Single Character
    MINUS, PLUS,
    ASTERISK, SLASH,
    GREATER_THAN, LESSER_THAN,
    RIGHT_PAREN, LEFT_PAREN,
    EQUAL, SEMICOLON,
    
    //Keyword
    V_,

    //Special Character
    NEXT_LINE,
    END_OF_FILE
};