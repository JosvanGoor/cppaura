#ifndef AURA_OBJECTS_OBJUPVALUE_H
#define AURA_OBJECTS_OBJUPVALUE_H

#include "../../value/value.h"
#include "../object/object.h"

namespace aura
{

    struct ObjUpvalue : public Object
    {
        Value *location;
        Value closed;
        ObjUpvalue *next;

        ObjUpvalue(Object *next, Value *slot);
    };

}

#endif