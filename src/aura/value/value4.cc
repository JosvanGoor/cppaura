#include "value.ih"

Value::Value(bool val)
:   type(ValueType::BOOL)
{
    as.boolean = val;
}