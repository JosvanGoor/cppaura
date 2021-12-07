#include "virtualmachine.ih"

VirtualMachine::~VirtualMachine()
{
    d_strings.clear();
    d_globals.clear();
    d_list_methods.clear();
    free_all_objects();

    delete[] d_stack;
    delete[] d_frames;
    delete[] d_gray_stack;

    if (d_bytes_allocated != 0)
        cerr << "Warning! " << d_bytes_allocated << " bytes still allocated.\n";
}