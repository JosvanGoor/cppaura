#ifndef AURA_OBJECTS_OBJLIST_H
#define AURA_OBJECTS_OBJLIST_H

#include "../object/object.h"
#include "../../allocator/allocator.h"
#include "../../nativeinterface/nativeinterface.h"
#include "../../value/value.h"
#include "../../valuetable/valuetable.h"

namespace aura
{

    struct ObjList : public Object
    {
        std::vector<Value, Allocator<Value>> list;

        ObjList(Object *next, MemoryManager *mm);
        void copy_from(Value *values, size_t num);

        static Value append(Object *obj, size_t num, Value *values, NativeInterface *ni);
        static Value concat(Object *obj, size_t num, Value *values, NativeInterface *ni);
        static Value insert(Object *obj, size_t num, Value *valies, NativeInterface *ni);
        static Value remove(Object *obj, size_t num, Value *values, NativeInterface *ni);
        static Value size(Object *obj, size_t num, Value *values, NativeInterface *ni);
        static Value resize(Object *obj, size_t num, Value *values, NativeInterface *ni);

        // insert list
        // slice
    };

}

#endif