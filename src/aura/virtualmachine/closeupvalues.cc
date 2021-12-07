#include "virtualmachine.ih"

void VirtualMachine::close_upvalues(Value *last)
{
    while (d_open_upvalues != nullptr && d_open_upvalues->location >= last)
    {
        ObjUpvalue *upvalue = d_open_upvalues;
        upvalue->closed = *upvalue->location;
        upvalue->location = &upvalue->closed;
        d_open_upvalues = upvalue->next;
    }
}