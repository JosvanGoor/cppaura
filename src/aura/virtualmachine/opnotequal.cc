#include "virtualmachine.ih"

void VirtualMachine::op_not_equal()
{
    Value rhs = pop();

    switch(peek(0).type)
    {
        case ValueType::INT:
            switch (rhs.type)
            {
                case ValueType::FLOAT: peek(0) = !(peek(0).as.integer == rhs.as.floating); break;
                default: peek(0) = !(peek(0) == rhs);
            }
            break;
        case ValueType::FLOAT:
            switch (rhs.type)
            {
                case ValueType::INT: peek(0) = !(peek(0).as.floating == rhs.as.integer); break;
                default: peek(0) = !(peek(0) == rhs);
            }
            break;
        default:
            peek(0) = !(peek(0) == rhs);
            break;
    }
}
