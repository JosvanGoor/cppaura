#include "debug.ih"

#include "debug.ih"

size_t compound_instruction(char const *name, Chunk const &chunk, size_t offset)
{
    uint8_t constant = chunk.code()[offset + 1];
    uint8_t op = chunk.code()[offset + 2];
    cout << setw(24) << setfill(' ') << left << name << " " << setw(4) << int(constant);
    cout << "'" << chunk.constant(constant);
    cout << "' (";

    switch (op)
    {
        case OP_ADD:        cout << "OP_ADD"; break;
        case OP_SUBSTRACT:  cout << "OP_SUBSTRACT"; break;
        case OP_MULTIPLY:   cout << "OP_MULTIPLY"; break;
        case OP_DIVIDE:     cout << "OP_DIVIDE"; break;
        case OP_MODULO:     cout << "OP_MODULO"; break;
        default:            cout << "unknown"; break;
    }
    cout << ")\n";

    return offset + 3;
}