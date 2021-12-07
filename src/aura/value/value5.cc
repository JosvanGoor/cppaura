#include "value.ih"

Value::Value(Object *obj)
:   type(ValueType::OBJECT)
{
    as.object = obj;
}