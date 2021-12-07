#include "scanner.ih"

Scanner::~Scanner()
{
    if (d_source)
        delete[] d_source;
}