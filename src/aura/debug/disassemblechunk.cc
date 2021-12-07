#include "debug.ih"

void aura::disassemble_chunk(Chunk const &chunk, char const *name)
{
    size_t length = chunk.code_length();

    cout << "== " << name << " (stack requirement: " << chunk.stack_requirement() <<") ==\n";

    for (size_t offset = 0; offset < length; /**/)
        offset = disassemble_instruction(chunk, offset);
    cout << "== " << name << " ==\n\n";
}