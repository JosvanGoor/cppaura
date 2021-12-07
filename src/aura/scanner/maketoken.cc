#include "scanner.ih"

Token Scanner::make_token(TokenType type)
{
    return Token 
    {
        type,
        d_start,
        size_t(d_current - d_start),
        d_line
    };
}