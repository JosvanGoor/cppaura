#include "compiler.ih"

void Compiler::emit_loop(uint8_t instruction, int loop_start)
{
    emit_byte(instruction);

    int offset = current_chunk()->code_length() - loop_start + 2;
    if (offset > UINT16_MAX)
        error("Loop body too large.");

    emit_short(offset);
}