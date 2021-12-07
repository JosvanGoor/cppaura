#include "object.ih"

Object::Object(Object *nxt, ObjectType tpe)
:   next(nxt),
    type(tpe),
    is_marked(false)
{
    
}