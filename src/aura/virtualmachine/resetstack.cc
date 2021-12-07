#include "virtualmachine.ih"

void VirtualMachine::reset_stack()
{
    d_stack_top = d_stack;
    d_frame_count = 0;
    d_native_ok = true;
}