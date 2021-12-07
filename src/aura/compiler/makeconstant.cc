#include "compiler.ih"

size_t Compiler::make_constant(Value value)
{
    d_vm->push(value);
    size_t index = current_chunk()->write_constant(value);
    d_vm->pop();

    if (index > UINT16_MAX)
    {
        error("Too many constants.");
        return index;
    }
    
    return index;
}