#include "virtualmachine.ih"

void VirtualMachine::mark_roots()
{
    // start by walking the stack
    for (Value *slot = d_stack; slot < d_stack_top; ++slot)
        mark_value(*slot);

    // mark globals
    d_globals.mark_contents(this);

    // mark closures / call stack
    for (size_t idx = 0; idx < d_frame_count; ++idx)
        mark_object(d_frames[idx].closure);

    // mark open upvalues
    for (ObjUpvalue *upvalue = d_open_upvalues; upvalue != nullptr; upvalue = upvalue->next)
        mark_object(upvalue);

    /*
        NATIVE ROOTS
    */
    d_list_methods.mark_contents(this);
}