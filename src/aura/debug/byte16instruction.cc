#include "debug.ih"

size_t byte16_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    uint16_t slot = chunk.code()[offset + 1] << 8;
    slot |= chunk.code()[offset + 2];
    cout << setw(24) << setfill(' ') << left << name << " " << setw(4) << slot << "\n";
    return offset + 3;
}