#include "compiler.ih"

void Compiler::declare_variable()
{
    if (d_compiler->scope_depth == 0)
        return; // its global, so we let the global stuff take over.

    Token *name = &d_previous;

    for (auto it = d_compiler->locals.rbegin(); it != d_compiler->locals.rend(); ++it)
    {
        if (it->depth != -1 && it->depth < d_compiler->scope_depth)
            break;

        if (identifiers_equal(name, &it->name))
            error("Variable with this name already declared in this scope.");
    }

    add_local(*name);
}