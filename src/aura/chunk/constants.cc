#include "chunk.ih"

std::vector<Value, Allocator<Value>> &Chunk::constants()
{
    return d_constants;
}