#include "compiler.ih"

void Compiler::emit_bytes(uint8_t byte1, uint8_t byte2)
{
    current_chunk()->write(byte1, d_previous.line);
    current_chunk()->write(byte2, d_previous.line);
}