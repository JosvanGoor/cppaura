#include "compiler.ih"

int Compiler::emit_jump(uint8_t instruction)
{
    emit_byte(instruction);
    emit_short(UINT16_MAX);
    return current_chunk()->code_length() - 2;
}