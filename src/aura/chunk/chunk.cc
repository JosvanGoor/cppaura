#include "chunk.ih"

Chunk::Chunk(MemoryManager *mm)
:   d_required_stack(0),
    d_code(Allocator<uint8_t>{mm}),
    d_line_info(Allocator<LineInfo>{mm}),
    d_constants(Allocator<Value>{mm})
{

}