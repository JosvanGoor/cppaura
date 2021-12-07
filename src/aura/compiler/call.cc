#include "compiler.ih"

void Compiler::call([[maybe_unused]] bool can_assign)
{
    uint8_t arg_count = argument_list();
    emit_bytes(OP_CALL, arg_count);
}