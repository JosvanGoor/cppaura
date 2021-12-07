#include "compiler.ih"

int Compiler::add_upvalue(LocalCompiler *compiler, uint16_t index, bool is_local)
{
    // no duplicates please!
    for (size_t idx = 0; idx < compiler->upvalues.size(); ++idx)
    {
        Upvalue *upvalue = &compiler->upvalues[idx];
        if (upvalue->index == index && upvalue->is_local == is_local)
            return idx;
    }

    if (compiler->upvalues.size() == UINT16_MAX)
    {
        error("Too many closure variables in function.");
        return 0;
    }

    // aight we good, make  a new one.
    ++compiler->function->upvalue_count;
    compiler->upvalues.push_back({index, is_local});
    return int(compiler->upvalues.size() - 1);
}