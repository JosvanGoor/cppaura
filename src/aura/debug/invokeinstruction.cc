#include "debug.ih"

size_t invoke_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    uint8_t constant = chunk.code()[offset + 1];
    uint8_t arg_count = chunk.code()[offset + 2];
    
    cout << setw(24) << setfill(' ') << left << name << " " << setw(4);
    cout << int(constant) << "'" << chunk.constant(constant).to_string();
    cout  << "' (" << int(arg_count) << " args)\n";

    return offset + 3;
}