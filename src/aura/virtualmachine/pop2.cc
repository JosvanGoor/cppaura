#include "virtualmachine.ih"

Value VirtualMachine::pop()
{
    --d_stack_top;
    return *d_stack_top;
}