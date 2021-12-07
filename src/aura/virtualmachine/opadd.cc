#include "virtualmachine.ih"

bool VirtualMachine::op_add()
{
    Value rhs = pop();

    switch(peek().type)
    {
        case ValueType::INT:
            switch (rhs.type)
            {
                case ValueType::INT: peek().as.integer += rhs.as.integer; break;
                case ValueType::FLOAT: peek() = peek().as.integer + rhs.as.floating; break;
                case ValueType::OBJECT:
                    if (rhs.as.object->is_type(ObjectType::STRING))
                    {
                        push(rhs);
                        concatenate();
                        break;
                    }
                    [[fallthrough]];
                default:
                    runtime_error("Operands must be of int, float or string type.");
                    return false;
            }
            break;
        case ValueType::FLOAT:
            switch (rhs.type)
            {
                case ValueType::INT: peek().as.floating += rhs.as.integer; break;
                case ValueType::FLOAT: peek().as.floating += rhs.as.floating; break;
                case ValueType::OBJECT:
                    if (rhs.as.object->is_type(ObjectType::STRING))
                    {
                        push(rhs);
                        concatenate();
                        break;
                    }
                    [[fallthrough]];
                default:
                    runtime_error("Operands must be of int, float or string type.");
                    return false;
            }
            break;
        case ValueType::OBJECT:
            if (peek().as.object->type == ObjectType::STRING)
            {
                push(rhs);
                concatenate();
                break;
            }
            [[fallthrough]];
        default:
            if (rhs.type == ValueType::OBJECT && rhs.as.object->is_type(ObjectType::STRING))
            {
                push(rhs);
                concatenate();
            }
            else
            {
                runtime_error("Operands must be int, float or string type.");
                return false;
            }
    }

    return true;
}