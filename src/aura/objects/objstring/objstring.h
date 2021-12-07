#ifndef AURA_OBJECTS_OBJSTRING_H
#define AURA_OBJECTS_OBJSTRING_H

#include <cstddef>
#include <cstdint>

#include "../object/object.h"

namespace aura
{
    struct ObjString : public Object
    {
        uint32_t hash;
        size_t length;
        char *chars;

        ObjString(Object *next, char *chars, size_t length, uint32_t hash);
    };
}

#endif