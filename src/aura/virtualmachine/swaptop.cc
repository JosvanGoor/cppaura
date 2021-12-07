#include "virtualmachine.ih"

void VirtualMachine::swap_top()
{
    Value temp = peek(1);
    peek(1) = peek();
    peek() = temp;
}