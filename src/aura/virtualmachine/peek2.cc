#include "virtualmachine.ih"

Value &VirtualMachine::peek(int distance)
{
    return d_stack_top[-1 - distance];
}

