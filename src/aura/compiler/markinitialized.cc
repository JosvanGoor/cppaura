#include "compiler.ih"

void Compiler::mark_initialized()
{
    if (d_compiler->scope_depth == 0)
        return;
        
    d_compiler->locals.back().depth = d_compiler->scope_depth;
}