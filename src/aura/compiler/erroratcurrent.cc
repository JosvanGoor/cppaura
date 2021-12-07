#include "compiler.ih"

void Compiler::error_at_current(char const *message)
{
    error_at(d_current, message);
}