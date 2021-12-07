#include "compiler.ih"

void Compiler::end_scope()
{
    --d_compiler->scope_depth;

    bool needs_close = false;
    size_t npop = 0;
    while (!d_compiler->locals.empty() && d_compiler->locals.back().depth > d_compiler->scope_depth)
    {
        if (d_compiler->locals.back().is_captured)
            needs_close = true;
        ++npop;

        d_compiler->locals.pop_back();
    }

    if (!d_compiler->loops.empty())
        d_compiler->loops.back().num_locals -= npop;

    emit_pop(npop);
    if (needs_close)
        emit_byte(OP_CLOSE_UPVALUES);
}