#include "memorymanager.h"

template <typename Obj>
void aura::MemoryManager::destroy_and_free(Obj *obj)
{
    if (obj == nullptr)
        return;

    obj->~Obj();
    deallocate(obj, sizeof(Obj));
}