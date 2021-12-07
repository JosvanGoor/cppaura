#include "scanner.ih"

Token Scanner::scan_identifier()
{
    while (isalpha(peek()) || isdigit(peek()) || '_' == peek())
        advance();

    return make_token(identifier_type());
}