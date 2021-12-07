#include "value.ih"

bool Value::is_obj_type(ObjectType type)
{
    return this->type == ValueType::OBJECT
        && as.object->is_type(type);
}