#include "memorymanager.ih"

MemoryManager::~MemoryManager()
{
    free_all_objects();
}