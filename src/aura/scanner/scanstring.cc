#include "scanner.ih"

Token Scanner::scan_string()
{
    while (peek() != '"' && !is_at_end())
    {
        if (peek() == '\n')
            ++d_line;
        advance();
    }

    if (is_at_end())
        return error_token("Unterminated string.");

    advance(); // closing quote
    return make_token(TokenType::STRING);
}