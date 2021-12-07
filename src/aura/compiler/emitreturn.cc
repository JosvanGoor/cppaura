#include "compiler.ih"

void Compiler::emit_return()
{
    if (d_compiler->type == FunctionType::INITIALIZER)
        emit_bytes(OP_GET_LOCAL, 0); // return this
    else
        emit_byte(OP_NIL);
        
    emit_byte(OP_RETURN);
}