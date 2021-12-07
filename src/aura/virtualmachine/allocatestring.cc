#include "virtualmachine.ih"

ObjString *VirtualMachine::allocate_string(char *chars, size_t length, uint32_t hash)
{
    ObjString *str = allocate_object<ObjString>(chars, length, hash);

    push(str);
    d_strings.set(str, Value{});
    pop();
    
    return str;
}