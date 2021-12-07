#include "compiler.ih"

void Compiler::variable(bool can_assign)
{
    named_variable(d_previous, can_assign);
}