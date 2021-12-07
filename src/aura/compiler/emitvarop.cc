#include "compiler.ih"

void Compiler::emit_var_op(int arg, uint8_t op, uint8_t op16)
{
    if (arg > UINT8_MAX || op == op16)
    {
        emit_byte(op16);
        emit_short(arg);
    }
    else
        emit_bytes(op, arg);
}