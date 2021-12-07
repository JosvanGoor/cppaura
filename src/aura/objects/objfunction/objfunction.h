#ifndef AURA_OBJECTS_OBJFUNCTION_H
#define AURA_OBJECTS_OBJFUNCTION_H

#include "../object/object.h"
#include "../../chunk/chunk.h"

namespace aura
{
    // forward decl
    class ObjString;

    struct ObjFunction : public Object
    {
        int arity;
        int upvalue_count;
        Chunk chunk;
        ObjString *name;

        ObjFunction(Object *next, MemoryManager *vm);
    };

}

#endif