#include "virtualmachine.ih"

void VirtualMachine::rebase_open_upvalues(Value *new_stack)
{
    ObjUpvalue *current = d_open_upvalues;

    while (current != nullptr)
    {
        current->location = &new_stack[current->location - d_stack];
        current = current->next;
    }
}