#include "debug.ih"

size_t simple_instruction(char const *name, size_t offset)
{
    cout << name << "\n";
    return offset + 1;
}