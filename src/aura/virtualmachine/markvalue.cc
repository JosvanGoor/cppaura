#include "virtualmachine.ih"

void VirtualMachine::mark_value(Value value)
{
    if (value.type != ValueType::OBJECT)
        return;

    mark_object(value.as.object);
}