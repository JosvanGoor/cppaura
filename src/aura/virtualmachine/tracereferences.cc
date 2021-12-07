#include "virtualmachine.ih"

void VirtualMachine::trace_references()
{
    while (d_gray_count > 0)
    {
        Object *object = d_gray_stack[--d_gray_count];
        blacken_object(object);
    }
}