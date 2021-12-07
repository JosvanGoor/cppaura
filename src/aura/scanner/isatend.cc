#include "scanner.ih"

bool Scanner::is_at_end()
{
    return *d_current == '\0';
}