#include "value.ih"

Value &Value::operator=(bool b)
{
    type = ValueType::BOOL;
    as.boolean = b;
    return *this;
}