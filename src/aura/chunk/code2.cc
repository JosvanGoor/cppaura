#include "chunk.ih"

uint8_t const *Chunk::code() const
{
    return d_code.data();
}