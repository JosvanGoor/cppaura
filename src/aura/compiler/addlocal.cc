#include "compiler.ih"

void Compiler::add_local(Token name)
{
    if (d_compiler->locals.size() == (UINT16_MAX + 1))
    {
        error("Too many local variables in function.");
        return;
    }

    d_compiler->locals.push_back({name, -1});
    if (!d_compiler->loops.empty())
        ++d_compiler->loops.back().num_locals;
}