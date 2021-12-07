#include "compiler.ih"

void Compiler::begin_loop(int loop_start)
{
    d_compiler->loops.push_back
    (
        {
            loop_start,
            0,
            {}
        }
    );
}