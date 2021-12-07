#include "scanner.ih"

char Scanner::advance()
{
    ++d_current;
    return d_current[-1];
}