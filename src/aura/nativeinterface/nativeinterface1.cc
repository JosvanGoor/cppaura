#include "nativeinterface.ih"

NativeInterface::NativeInterface(MemoryManager *mm)
:   d_native_ok(true),
    d_list_methods(mm)
{ }