#include "debug.ih"

size_t byte_instruction(char const *name, Chunk const &chunk, size_t offset, bool compound)
{
    uint16_t slot = chunk.code()[offset + 1];
    cout << setw(24) << setfill(' ') << left << name;

    if (compound)
    {
        switch (slot)
        {
            case OP_ADD:        cout << " OP_ADD"; break;
            case OP_SUBSTRACT:  cout << " OP_SUBSTRACT"; break;
            case OP_MULTIPLY:   cout << " OP_MULTIPLY"; break;
            case OP_DIVIDE:     cout << " OP_DIVIDE"; break;
            case OP_MODULO:     cout << " OP_MODULO"; break;
            default:            cout << " unknown"; break;
        }
    }
    else
        cout << " " << setw(4) << slot;
    cout << "\n";

    return offset + 2;
}