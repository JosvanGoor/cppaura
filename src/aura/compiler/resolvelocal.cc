#include "compiler.ih"

int Compiler::resolve_local(LocalCompiler *compiler, Token *name)
{
    for (int index = compiler->locals.size(); index--; /**/)
    {
        if (identifiers_equal(name, &compiler->locals[index].name))
        {

            if (compiler->locals[index].depth == -1)
                error("Cannot read local variable in its own initialized.");
            return index;
        }
    }

    return -1;
}