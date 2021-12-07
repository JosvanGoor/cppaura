#include "debug.ih"

size_t list_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    uint16_t length = chunk.code()[offset + 1] << 8;
    length |= chunk.code()[offset + 2];
    cout << setw(24) << setfill(' ') << left << name << " " << length << "\n";
    return offset + 3;
}