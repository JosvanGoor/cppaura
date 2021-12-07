#include "scanner.ih"

char Scanner::peek()
{
    return *d_current;
}