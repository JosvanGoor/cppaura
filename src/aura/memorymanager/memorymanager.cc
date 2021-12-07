#include "memorymanager.ih"

MemoryManager::MemoryManager()
:   d_objects(nullptr),
    d_next_collect(1024),
    d_bytes_allocated(0),
    d_collect_callback()
{

}