#include "value.ih"

string Value::to_string() const
{
    switch (type)
    {
        case ValueType::NIL:        return "nil";
        case ValueType::BOOL:       return as.boolean ? "true" : "false";
        case ValueType::INT:        return std::to_string(as.integer);
        case ValueType::FLOAT:      return std::to_string(as.floating);
        case ValueType::OBJECT:     return aura::to_string(as.object);
        default:                    return "unreachable";
    }
}