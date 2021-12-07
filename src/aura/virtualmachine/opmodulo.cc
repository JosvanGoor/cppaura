#include "virtualmachine.ih"

bool VirtualMachine::op_modulo()
{
    Value rhs = pop();
    
    if (rhs.type != ValueType::INT || peek(0).type != ValueType::INT)
    {
        runtime_error("Operands must be of int type.");
        return false;
    }

    peek(0).as.integer %= rhs.as.integer;
    return true;
}