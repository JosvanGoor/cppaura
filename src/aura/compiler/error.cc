#include "compiler.ih"

void Compiler::error(char const *message)
{
    error_at(d_previous, message);
}