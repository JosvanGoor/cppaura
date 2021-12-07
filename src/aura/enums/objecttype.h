#ifndef AURA_OBJECTTYPE_H
#define AURA_OBJECTTYPE_H

namespace aura
{

    enum class ObjectType
    {
        BOUND_METHOD,
        CLASS,
        CLOSURE,
        FUNCTION,
        INSTANCE,
        LIST,
        NATIVE_FUNCTION,
        NATIVE_METHOD,
        UPVALUE,
        STRING
    };

}

#endif