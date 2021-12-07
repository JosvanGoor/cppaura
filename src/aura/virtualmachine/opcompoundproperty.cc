#include "virtualmachine.ih"

bool VirtualMachine::op_compound_property(ObjString *name, uint8_t opcode)
{
    if (!peek(1).is_obj_type(ObjectType::INSTANCE))
    {
        runtime_error("Only instances have properties.");
        return false;
    }

    ObjInstance *instance = reinterpret_cast<ObjInstance*>(peek(1).as.object);

    Value value;
    if (!instance->fields.get(name, &value))
    {
        runtime_error("Referenced before assignment.");
        return false;
    }

    push(value);
    swap_top();

    bool result;

    // perform the op
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

    if (result)
    {
        // store the result
        instance->fields.set(name, peek());
        peek(1) = peek();
        pop();
    }
    
    return result;
}