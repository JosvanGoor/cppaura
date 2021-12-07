#include "value.ih"

bool Value::operator==(Value const &val) // for const list, most strict way of equals.
{
    if (type != val.type)
        return false;

    switch (type)
    {
        case ValueType::NIL:    return true;
        case ValueType::INT:    return as.integer == val.as.integer;
        case ValueType::FLOAT:  return as.floating == val.as.floating;
        case ValueType::BOOL:   return as.boolean == val.as.boolean;
        case ValueType::OBJECT: return as.object == val.as.object;

        default: return false; // unreachable
    }
}
