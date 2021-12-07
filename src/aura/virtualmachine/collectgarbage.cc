#include "virtualmachine.ih"

void VirtualMachine::collect_garbage()
{
    #ifdef DEBUG_LOG_GC
    // cout << "-- GC begin\n";
    size_t before = d_bytes_allocated;
    time_t start = clock();
    #endif

    mark_roots();
    trace_references();

    d_strings.remove_white();
    sweep();

    d_next_collect = d_bytes_allocated * GC_HEAP_GROW_FACTOR;

    #ifdef DEBUG_LOG_GC
    // cout << "-- GC end\n";
    cout << ">> GC collected " << (before - d_bytes_allocated);
    cout << " bytes in " << (float(clock() - start) / CLOCKS_PER_SEC) * 1000.0 << " ms ";
    cout << "(from " << before << " to " << d_bytes_allocated;
    cout << ") next at " << d_next_collect << " bytes allocated. << \n";
    #endif
}