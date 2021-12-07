#ifndef AURA_OBJECTS_OBJINSTANCE_H
#define AURA_OBJECTS_OBJINSTANCE_H

#include "../object/object.h"
#include "../objclass/objclass.h"
#include "../../memorymanager/memorymanager.h"
#include "../../valuetable/valuetable.h"

namespace aura
{

    struct ObjInstance : public Object
    {
        ObjClass *klass;
        ValueTable fields;

        ObjInstance(Object *next, MemoryManager *mm, ObjClass *klass);
    };

}

#endif