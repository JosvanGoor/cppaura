#include "chunk.ih"

size_t Chunk::stack_requirement() const
{
    return d_required_stack;
}