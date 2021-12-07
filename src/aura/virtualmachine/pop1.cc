#include "virtualmachine.ih"

void VirtualMachine::pop(size_t num)
{
    d_stack_top -= num;
}