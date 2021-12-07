#include "compiler.ih"

void Compiler::patch_jump(int offset)
{
    // -2 to adjust for the bytecode for the jump offset itself.
    int jump = current_chunk()->code_length() - offset - 2;

    if (jump > UINT16_MAX)
        error("Too much code to jump over.");

    current_chunk()->code()[offset] = (jump >> 8) & 0xff;
    current_chunk()->code()[offset + 1] = jump & 0xff;
}