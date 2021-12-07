#include "virtualmachine.ih"

void VirtualMachine::mark_object(Object *object)
{
    if (object == nullptr)
        return;
    if (object->is_marked)
        return;
    
    object->is_marked = true;

    if (d_gray_capacity < (d_gray_count + 1))
        grow_gray_stack();
    
    d_gray_stack[d_gray_count++] = object;
}