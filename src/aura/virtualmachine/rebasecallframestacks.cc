#include "virtualmachine.ih"

void VirtualMachine::rebase_callframe_stacks(Value *new_stack)
{
    for (size_t idx = 0; idx < d_frame_count; ++idx)
        d_frames[idx].slots = &new_stack[d_frames[idx].slots - d_stack];
}