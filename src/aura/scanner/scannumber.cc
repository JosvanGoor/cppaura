#include "scanner.ih"

Token Scanner::scan_number()
{
    while (isdigit(peek()))
        advance();

    if (peek() == '.' && isdigit(peek_next()))
    {
        advance(); // consume the '.'

        while (isdigit(peek()))
            advance();

        return make_token(TokenType::FLOAT);
    }

    return make_token(TokenType::INTEGER);
}