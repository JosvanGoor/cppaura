#ifndef AURA_OBJECTS_OBJBOUNDMETHOD_H
#define AURA_OBJECTS_OBJBOUNDMETHOD_H

#include "../object/object.h"
#include "../objclosure/objclosure.h"
#include "../../value/value.h"

namespace aura
{

    struct ObjBoundMethod : public Object
    {
        Value receiver;
        ObjClosure *method;

        ObjBoundMethod(Object *next, Value receiver, ObjClosure *method);
    };

}

#endif