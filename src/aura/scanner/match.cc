#include "scanner.ih"

bool Scanner::match(char ch)
{
    if (is_at_end())
        return false;
    if (*d_current != ch)
        return false;

    ++d_current;
    return true;
}