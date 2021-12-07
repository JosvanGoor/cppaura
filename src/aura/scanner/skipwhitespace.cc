#include "scanner.ih"

void Scanner::skip_whitespace()
{
    while (true)
    {
        char ch = peek();
        switch (ch)
        {
            case ' ': [[fallthrough]];
            case '\r': [[fallthrough]];
            case '\t':
                advance();
                break;

            case '\n':
                ++d_line;
                advance();
                break;

            case '/':
                if (peek_next() == '/')
                {
                    while (peek() != '\n' && !is_at_end())
                        advance();
                } 
                else return;
                break;
            default:
                return;
        }
    }
}