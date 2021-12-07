#include "memorymanager.ih"

void MemoryManager::free_all_objects()
{
    Object *object = d_objects;
    
    while (object != nullptr)
    {
        Object *next = object->next;
        deallocate_object(object);
        object = next;
    }

    d_objects = nullptr;
}