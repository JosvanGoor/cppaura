#include "virtualmachine.ih"

bool VirtualMachine::op_compound_subscript(uint8_t opcode)
{
    Value index;
    // stack is "bot [List] [Index] [Value] top"

    // GET PART
    if (peek(2).is_obj_type(ObjectType::LIST))
    {
        if (peek(1).type != ValueType::INT)
        {
            runtime_error("List index must be an integer.");
            return false;
        }

        index = peek(1);
        ObjList *list = reinterpret_cast<ObjList*>(peek(2).as.object);

        if (index.as.integer < 0 || size_t(index.as.integer) >= list->list.size())
        {
            runtime_error("Index out of bounds.");
            return false;
        }

        peek(1) = list->list[index.as.integer];
    }
    else
    {
        runtime_error("Only lists are subscriptable.");
        return false;
    }

    // OP PART
    bool result;
    switch (opcode)
    {
        case OP_ADD:
            result = op_add();
            break;
        case OP_SUBSTRACT:
            result = numeric_binary<minus<int64_t>, minus<double>>();
            break;
        case OP_MULTIPLY:
            result = numeric_binary<multiplies<int64_t>, multiplies<double>>();
            break;
        case OP_DIVIDE:
            result = numeric_binary<divides<int64_t>, divides<double>>();
            break;
        case OP_MODULO:
            result = op_modulo();
            break;
        default:
            runtime_error("Malformed bytecode.");
            return false;
    }

    if (!result)
        return false;
    
    // SET PART
    if (peek(1).is_obj_type(ObjectType::LIST))
    {
        ObjList *list = reinterpret_cast<ObjList*>(peek(1).as.object);
        list->list[index.as.integer] = peek();
        peek(1) = peek();
        pop();
    }
    else
    {
        runtime_error("FATAL OPCODE ERROR");
        return false;
    }

    return true;
}