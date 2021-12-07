#include "scanner.ih"

Scanner::Scanner(char const *source)
:   d_source(source),
    d_line(1),
    d_start(source),
    d_current(source)
{
}