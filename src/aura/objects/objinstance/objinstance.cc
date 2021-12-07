#include "objinstance.h"

using namespace std;
using namespace aura;

ObjInstance::ObjInstance(Object *next, MemoryManager *mm, ObjClass *klass)
:   Object(next, ObjectType::INSTANCE),
    klass(klass),
    fields(mm)
{

}