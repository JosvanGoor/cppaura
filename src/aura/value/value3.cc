#include "value.ih"

Value::Value(double val)
:   type(ValueType::FLOAT)
{
    as.floating = val;
}