#include "memorymanager.ih"

void MemoryManager::deallocate(void *ptr, size_t numbytes)
{
    d_bytes_allocated -= numbytes;
    free(ptr);
}
