#ifndef AURA_OBJECTS_NATIVE_FUNCTION_H
#define AURA_OBJECTS_NATIVE_FUNCTION_H

#include <cstddef>
#include <functional>

#include "../../nativeinterface/nativeinterface.h"
#include "../../objects/object/object.h"
#include "../../value/value.h"

namespace aura
{
    using NativeFunction = std::function<Value (size_t, Value*, NativeInterface*)>;

    struct ObjNativeFunction : public Object
    {
        NativeFunction function;

        ObjNativeFunction(Object *next, NativeFunction func);
    };

}

#endif