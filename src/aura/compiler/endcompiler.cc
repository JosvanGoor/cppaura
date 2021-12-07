#include "compiler.ih"

ObjFunction *Compiler::end_compiler()
{
    emit_return();
    ObjFunction *function = d_compiler->function;
    function->chunk.set_stack_requirement(chunk_max_stacksize(&function->chunk));

    // DEBUG PRINT CODE
    if (!d_had_error)
        disassemble_chunk(*current_chunk(), function->name != nullptr ? function->name->chars : "<script>");

    d_compiler = d_compiler->enclosing;
    return function;
}