#include "virtualmachine.ih"

template <typename Operi, typename Operf>
bool VirtualMachine::numeric_binary()
{
    Value rhs = pop();

    switch(peek(0).type)
    {
        case ValueType::INT:
            switch (rhs.type)
            {
                case ValueType::INT: peek(0) = Operi{}(peek(0).as.integer, rhs.as.integer); break;
                case ValueType::FLOAT: peek(0) = Operf{}(peek(0).as.integer, rhs.as.floating); break;
                default:
                    runtime_error("Operands must be of int or float type.");
                    return false;
            }
            break;
        case ValueType::FLOAT:
            switch (rhs.type)
            {
                case ValueType::INT: peek(0) = Operf{}(peek(0).as.floating, rhs.as.integer); break;
                case ValueType::FLOAT: peek(0) = Operf{}(peek(0).as.floating, rhs.as.floating); break;
                default:
                    runtime_error("Operands must be of int or float type.");
                    return false;
            }
            break;
        default:
            runtime_error("Operands must be int, float or string type.");
            return false;
    }

    return true;
}