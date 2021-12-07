#include "virtualmachine.ih"

void VirtualMachine::grow_gray_stack()
{
    size_t newcap = d_gray_capacity == 0 ? 8 : d_gray_capacity * 2;
    Object **newstack = new Object*[newcap];

    for (size_t idx = 0; idx < d_gray_capacity; ++idx)
        newstack[idx] = d_gray_stack[idx];

    // init rest of list, should not be nessecary.
    d_gray_capacity = newcap;
    delete[] d_gray_stack;
    d_gray_stack = newstack;
}