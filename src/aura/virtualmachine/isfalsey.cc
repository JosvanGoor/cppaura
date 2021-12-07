#include "virtualmachine.ih"

// specifically, nil is evaluated as false, and false is evaluated as false.
// all other possible values are true.

bool VirtualMachine::is_falsey(Value const &value)
{
    return value.type == ValueType::NIL
        || (value.type == ValueType::BOOL && !value.as.boolean);
}