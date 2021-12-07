#include "value.ih"

Value::Value(int64_t val)
:   type(ValueType::INT)
{
    as.integer = val;
}