#include "virtualmachine.ih"

void VirtualMachine::mark_array(vector<Value, Allocator<Value>> &array)
{
    for (Value &value : array)
        mark_value(value);
}