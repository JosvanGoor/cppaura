#ifndef AURA_OBJECTS_OBJECT_H
#define AURA_OBJECTS_OBJECT_H

/* Root class of all object types for aura */
#include "../../enums/objecttype.h"

namespace aura
{

    struct Object
    {
        Object *next;
        ObjectType type;
        bool is_marked;

        Object(Object *next, ObjectType type);

        bool is_type(ObjectType type);
    };

}

#endif