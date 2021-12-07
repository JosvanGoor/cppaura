#include "memorymanager.ih"

[[nodiscard]] void *MemoryManager::allocate(size_t numbytes)
{
    d_bytes_allocated += numbytes;

    #ifdef DEBUG_STRESS_GC
        d_collect_callback();
    #endif

    #ifndef DEBUG_STRESS_GC
    if(d_bytes_allocated > d_next_collect)
        d_collect_callback();
    #endif

    return malloc(numbytes);
}