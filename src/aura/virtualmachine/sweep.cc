#include "virtualmachine.ih"

void VirtualMachine::sweep()
{
    Object *previous = nullptr;
    Object *object = d_objects;

    while (object != nullptr)
    {
        if (object->is_marked)
        {
            object->is_marked = false;
            previous = object;
            object = object->next;
        }
        else
        {
            Object *unreached = object;
            object = object->next;

            if (previous != nullptr)
                previous->next = object;
            else
                d_objects = object;

            deallocate_object(unreached);
        }
    }
}