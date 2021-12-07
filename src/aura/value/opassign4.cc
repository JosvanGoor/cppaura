#include "value.ih"

Value &Value::operator=(Object *obj)
{
    type = ValueType::OBJECT;
    as.object = obj;
    return *this;
}