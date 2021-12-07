#include "compiler.ih"

int Compiler::chunk_max_stacksize(Chunk *chunk)
{
    int max = 0;
    int current = 0;

    auto update = [&](int val)
    {
        current += val;
        max = std::max(max, current);
    };

    for (size_t idx = 0; idx < chunk->code_length(); )
    {
        auto [effect, offset] = opcode_stack_effect(chunk, idx);
        idx += offset;
        update(effect);
    }

    return max; // +1 because the calling closure will be put on the stack aswell.
}