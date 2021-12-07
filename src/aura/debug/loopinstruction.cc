#include "debug.ih"

size_t loop_instruction(char const *name, int sign, Chunk const &chunk, size_t offset)
{
    uint16_t jump = (uint16_t)(chunk.code()[offset + 1] << 8);
    jump |= chunk.code()[offset + 2];
    uint16_t pops = (uint16_t)(chunk.code()[offset + 3] << 8);
    pops |= chunk.code()[offset + 4];

    cout << setfill(' ') << left;
    cout << setw(24) << name << " " << setw(4) << offset;
    cout << " -> " << offset + 3 + sign * jump;
    cout << " (pop " << pops << ")\n";
    return offset + 5;
}