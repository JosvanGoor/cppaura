#include "compiler.ih"

int Compiler::resolve_upvalue(LocalCompiler *compiler, Token *name)
{
    if (compiler->enclosing == nullptr) // script/global level.
        return -1;

    int local = resolve_local(compiler->enclosing, name);
    if (local != -1)
    {
        compiler->enclosing->locals[local].is_captured = true;
        return add_upvalue(compiler, uint16_t(local), true);
    }

    int upvalue = resolve_upvalue(compiler->enclosing, name);
    if (upvalue != -1)
        return add_upvalue(compiler, uint16_t(upvalue), false);

    return -1;
}