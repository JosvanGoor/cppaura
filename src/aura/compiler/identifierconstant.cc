#include "compiler.ih"

int Compiler::identifier_constant(Token *name)
{
    return int(make_constant(d_vm->copy_string(name->start, name->length)));
}