#include "scanner.ih"

Scanner &Scanner::operator=(Scanner &&other)
{
    char const *temp = d_source;

    d_source = other.d_source;
    d_line = other.d_line;
    d_start = other.d_start;
    d_current = other.d_current;

    other.d_source = temp;
    other.d_line = 0;
    other.d_start = temp;
    other.d_current = temp;
    return *this;
}