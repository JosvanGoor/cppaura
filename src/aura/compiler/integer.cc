#include "compiler.ih"

void Compiler::integer([[maybe_unused]] bool can_assign)
{
    int64_t value = stol(string{d_previous.start, d_previous.start + d_previous.length});

    switch(value)
    {
        case 0: emit_byte(OP_ZERO); break;
        case 1: emit_byte(OP_ONE); break;
        default: emit_constant(value); break;
    }   
}