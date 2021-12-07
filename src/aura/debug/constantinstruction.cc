#include "debug.ih"

size_t constant_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    uint8_t constant = chunk.code()[offset + 1];
    cout << setw(24) << setfill(' ') << left << name << " " << setw(4) << int(constant);
    cout << "'" << chunk.constant(constant) << "'\n";
    return offset + 2;
}