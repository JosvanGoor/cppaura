#include "compiler.ih"

void Compiler::emit_byte(uint8_t byte)
{
    current_chunk()->write(byte, d_previous.line);
}