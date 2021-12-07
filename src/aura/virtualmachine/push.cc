#include "virtualmachine.ih"

void VirtualMachine::push(Value const &value)
{
    *d_stack_top = value;
    ++d_stack_top;
}