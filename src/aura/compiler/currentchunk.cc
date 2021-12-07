#include "compiler.ih"

Chunk *Compiler::current_chunk()
{
    return &d_compiler->function->chunk;
}