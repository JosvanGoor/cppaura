#include "virtualmachine.ih"

ObjString *VirtualMachine::copy_string(char const *chars, size_t length)
{
    uint32_t hash = hash_string(chars, length);
    ObjString *interned = d_strings.find_string(chars, length, hash);

    if (interned != nullptr)
        return interned;

    char *heap_chars = reinterpret_cast<char*>(allocate(sizeof(char) * (length + 1)));
    memcpy(heap_chars, chars, length);
    heap_chars[length] = '\0';

    return allocate_string(heap_chars, length, hash);
}