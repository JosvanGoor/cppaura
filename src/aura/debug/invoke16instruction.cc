#include "debug.ih"

size_t invoke16_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    uint16_t constant = chunk.code()[offset + 1] << 8;
    constant |= chunk.code()[offset + 2];
    uint8_t arg_count = chunk.code()[offset + 3];
    
    cout << setw(24) << setfill(' ') << left << name << " " << setw(4);
    cout << int(constant) << "'" << chunk.constant(constant).to_string();
    cout  << "' (" << int(arg_count) << " args)\n";

    return offset + 4;
}