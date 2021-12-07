#include "compiler.ih"

void Compiler::end_loop()
{
    vector<size_t> &breaks = d_compiler->loops.back().breaks;

    for (size_t idx = 0; idx < breaks.size(); ++idx)
        patch_jump(breaks[idx]);
    
    d_compiler->loops.pop_back();
}