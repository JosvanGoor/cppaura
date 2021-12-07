#include "compiler.ih"

void Compiler::emit_short(uint16_t bytes)
{
    current_chunk()->write((bytes >> 8) & 0xff, d_previous.line);
    current_chunk()->write(bytes & 0xff, d_previous.line);
}