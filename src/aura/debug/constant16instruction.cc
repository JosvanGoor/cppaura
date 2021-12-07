#include "debug.ih"

size_t constant16_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    size_t constant = uint16_t((chunk.code()[offset + 1] << 8) | chunk.code()[offset + 2]);
    cout << setw(24) << setfill(' ') << left << name << " " << setw(4) << constant;
    /* TODO: replace met value::to_string */
    cout << "'" << chunk.constant(constant) << "'\n";
    return offset + 3;
}