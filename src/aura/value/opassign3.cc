#include "value.ih"

Value &Value::operator=(int64_t val)
{
    type = ValueType::INT;
    as.integer = val;
    return *this;
}