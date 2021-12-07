#ifndef AURA_TOKENTYPE_H
#define AURA_TOKENTYPE_H

namespace aura
{

    enum class TokenType
    {
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        COLON,
        COMMA,
        DOT,
        MINUS,
        PERCENT,
        PLUS,
        QUESTIONMARK,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character tokens.
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // compound tokens
        PLUS_EQUALS,
        MINUS_EQUALS,
        STAR_EQUALS,
        SLASH_EQUALS,
        PERCENT_EQUALS,

        // Literals.
        IDENTIFIER,
        STRING,
        INTEGER,
        FLOAT,

        // Keywords.                                        
        AND,
        BREAK,
        CLASS,
        CONTINUE,
        ELSE,
        FALSE,
        FOR,
        FUN,
        IF,
        ISA,
        NIL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,

        // special
        ERROR,
        EOS
    };

}

#endif