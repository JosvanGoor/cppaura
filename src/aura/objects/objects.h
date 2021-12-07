#ifndef AURA_OBJECTS_H
#define AURA_OBJECTS_H

#include <iostream>

#include "object/object.h"
#include "objboundmethod/objboundmethod.h"
#include "objclass/objclass.h"
#include "objclosure/objclosure.h"
#include "objfunction/objfunction.h"
#include "objlist/objlist.h"
#include "objnativefunction/objnativefunction.h"
#include "objnativemethod/objnativemethod.h"
#include "objinstance/objinstance.h"
#include "objstring/objstring.h"

namespace aura
{

    // forward decl
    class VirtualMachine;

    std::string to_string(Object *obj);
    std::ostream &operator<<(std::ostream &out, Object *obj);

}

#endif