#include "scanner.ih"

Token Scanner::error_token(char const *message)
{
    return Token
    {
        TokenType::ERROR,
        message,
        strlen(message),
        d_line
    };
}