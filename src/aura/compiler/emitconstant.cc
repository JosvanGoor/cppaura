#include "compiler.ih"

void Compiler::emit_constant(Value value)
{
    size_t index = make_constant(value);
    
    if (index > UINT8_MAX)
    {
        emit_byte(OP_CONSTANT_16);
        emit_short(index);
    }
    else
    {
        emit_bytes(OP_CONSTANT, index);
    }
}