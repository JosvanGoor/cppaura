#include "compiler.ih"

void Compiler::string_([[maybe_unused]] bool can_assign)
{
    // +1 & -2 to ignore '"'s
    emit_constant(d_vm->copy_string(d_previous.start + 1, d_previous.length - 2));
}