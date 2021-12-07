#include "compiler.ih"

void Compiler::emit_pop(uint32_t num)
{
    if (num == 0)
        return;
    
    if (num == 1)
        emit_byte(OP_POP);
    else if (num <= UINT8_MAX)
        emit_bytes(OP_POP_N, num);
    else if (num <= UINT16_MAX)
    {
        emit_byte(OP_POP_N_16);
        emit_short(num);
    }
    else
    {
        error("Can't pop more than 65535 items at the same time.");
    }
}