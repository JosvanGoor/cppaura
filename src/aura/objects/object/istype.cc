#include "object.ih"

bool Object::is_type(ObjectType type)
{
    return this->type == type;
}