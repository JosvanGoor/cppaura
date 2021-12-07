#include "chunk.ih"

void Chunk::write(uint8_t byte, size_t line)
{
    write_line(line);
    d_code.push_back(byte);
}