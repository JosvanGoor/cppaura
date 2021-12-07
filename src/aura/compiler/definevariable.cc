#include "compiler.ih"

void Compiler::define_variable(size_t global)
{
    if (d_compiler->scope_depth > 0)
    {
        mark_initialized();
        return; // its local.
    }

    // emit_var_op(global, OP_DEFINE_GLOBAL, OP_DEFINE_GLOBAL_16);
    
    if (global > UINT8_MAX)
    {
        emit_byte(OP_DEFINE_GLOBAL_16);
        emit_short(global);
    }
    else
        emit_bytes(OP_DEFINE_GLOBAL, global);
}