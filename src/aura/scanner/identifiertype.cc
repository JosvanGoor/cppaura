#include "scanner.ih"

TokenType Scanner::identifier_type()
{
    static auto check_keyword = [&](size_t start, size_t length, char const *rest, TokenType type)
    {
        if (size_t(d_current - d_start) != start + length)
            return TokenType::IDENTIFIER;
        if (memcmp(d_start + start, rest, length) == 0)
            return type;
        return TokenType::IDENTIFIER;
    };

    switch(d_start[0])
    {
        case 'a': return check_keyword(1, 2, "nd", TokenType::AND);
        case 'b': return check_keyword(1, 4, "reak", TokenType::BREAK);
        case 'e': return check_keyword(1, 3, "lse", TokenType::ELSE);
        case 'n': return check_keyword(1, 2, "il", TokenType::NIL);
        case 'o': return check_keyword(1, 1, "r", TokenType::OR);
        case 'p': return check_keyword(1, 4, "rint", TokenType::PRINT);
        case 'r': return check_keyword(1, 5, "eturn", TokenType::RETURN);
        case 's': return check_keyword(1, 4, "uper", TokenType::SUPER);
        case 'v': return check_keyword(1, 2, "ar", TokenType::VAR);
        case 'w': return check_keyword(1, 4, "hile", TokenType::WHILE);
        
        case 'c':
        {
            if(d_current - d_start > 1)
            {
                switch(d_start[1])
                {
                    case 'l': return check_keyword(2, 3, "ass", TokenType::CLASS);
                    case 'o': return check_keyword(2, 6, "ntinue", TokenType::CONTINUE);
                }
            }
            break;
        }

        case 'f':
            if (d_current - d_start > 1)
            {
                switch (d_start[1])
                {
                    case 'a': return check_keyword(2, 3, "lse", TokenType::FALSE);
                    case 'o': return check_keyword(2, 1, "r", TokenType::FOR);
                    case 'u': return check_keyword(2, 1, "n", TokenType::FUN);
                }
            }
            break;
        
        case 'i':
            if (d_current - d_start > 1)
            {
                switch (d_start[1])
                {
                    case 'f': return TokenType::IF;
                    case 's': return check_keyword(2, 1, "a", TokenType::ISA);
                }
            }
            break;

        case 't':
            if (d_current - d_start > 1)
            {
                switch(d_start[1])
                {
                    case 'h': return check_keyword(2, 2, "is", TokenType::THIS);
                    case 'r': return check_keyword(2, 2, "ue", TokenType::TRUE);
                }
            }
            break;
    }
    
    return TokenType::IDENTIFIER;
}