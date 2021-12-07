#include "scanner.ih"

char Scanner::peek_next()
{
    if (is_at_end())
        return '\0';
    return d_current[1];
}