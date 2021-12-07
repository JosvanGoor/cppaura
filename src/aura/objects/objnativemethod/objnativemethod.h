#ifndef AURA_OBJECTS_OBJNATIVEMETHOD_H
#define AURA_OBJECTS_OBJNATIVEMETHOD_H

#include <cstddef>
#include <functional>

#include "../object/object.h"
#include "../../nativeinterface/nativeinterface.h"
#include "../../value/value.h"

namespace aura
{

    using NativeMethod = std::function<Value (Object*, size_t, Value*, NativeInterface*)>;

    struct ObjNativeMethod : public Object
    {
        NativeMethod method;

        ObjNativeMethod(Object *next, NativeMethod method);
    };

}

#endif