#include "virtualmachine.ih"

ObjUpvalue *VirtualMachine::capture_upvalue(Value *local)
{
    ObjUpvalue *prev_upvalue = nullptr;
    ObjUpvalue *upvalue = d_open_upvalues;

    while (upvalue != nullptr && upvalue->location > local)
    {
        prev_upvalue = upvalue;
        upvalue = upvalue->next;
    }

    if (upvalue != nullptr && upvalue->location == local)
        return upvalue;
 
    ObjUpvalue *new_upvalue = allocate_object<ObjUpvalue>(local);
    new_upvalue->next = upvalue;

    if (prev_upvalue == nullptr)
        d_open_upvalues = new_upvalue;
    else
        prev_upvalue->next = new_upvalue;

    return new_upvalue;
}