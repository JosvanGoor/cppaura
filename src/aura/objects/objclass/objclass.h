#ifndef AURA_OBJECTS_OBJCLASS_H
#define AURA_OBJECTS_OBJCLASS_H

#include "../object/object.h"
#include "../objstring/objstring.h"
#include "../../valuetable/valuetable.h"

namespace aura
{

    struct ObjClass : public Object
    {
        ObjString *name;
        ValueTable methods;

        ObjClass(Object *next, MemoryManager *mm, ObjString *name);
    };

}

#endif