#include "compiler.ih"

void Compiler::begin_scope()
{
    ++d_compiler->scope_depth;
}