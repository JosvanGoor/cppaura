#include "virtualmachine.ih"

ObjString *VirtualMachine::take_string(char *chars, size_t length)
{
    uint32_t hash = hash_string(chars, length);
    ObjString *interned = d_strings.find_string(chars, length, hash);

    if (interned != nullptr)
    {
        deallocate(chars, sizeof(char) * (length + 1));
        return interned;
    }
    

    return allocate_string(chars, length, hash);
}