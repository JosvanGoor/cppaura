#include "virtualmachine.ih"

void VirtualMachine::grow_callstack()
{
    size_t new_size = d_frame_capacity == 0 ? 8 : 2 * d_frame_capacity;
    cout << ">> Growing callstack from " << d_frame_capacity << " to " << new_size << "<<\n";

    CallFrame *newframes = new CallFrame[new_size];

    // copy over existing frames;
    std::copy(d_frames, d_frames + d_frame_capacity, newframes);
    delete[] d_frames;

    d_frames = newframes;
    d_frame_capacity = new_size;
}