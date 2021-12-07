#include "virtualmachine.ih"

Value &VirtualMachine::peek()
{
    return d_stack_top[-1];
}