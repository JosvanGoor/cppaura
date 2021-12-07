#include "value.ih"

Value &Value::operator=(double val)
{
    type = ValueType::FLOAT;
    as.floating = val;
    return *this;
}