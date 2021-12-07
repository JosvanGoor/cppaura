#include "chunk.ih"

Value const &Chunk::constant(size_t index) const
{
    return d_constants[index];
}