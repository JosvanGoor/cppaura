#ifndef AURA_OBJECTS_OBJCLOSURE_H
#define AURA_OBJECTS_OBJCLOSURE_H

#include "../objfunction/objfunction.h"
#include "../objupvalue/objupvalue.h"
#include "../../memorymanager/memorymanager.h"

namespace aura
{

    struct ObjClosure : public Object
    {
        ObjFunction *function;
        ObjUpvalue **upvalues;
        int upvalue_count;

        ObjClosure(Object *next, MemoryManager *mm, ObjFunction *function);
    };

}

#endif