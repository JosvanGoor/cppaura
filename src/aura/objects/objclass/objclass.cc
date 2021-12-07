#include "objclass.h"

using namespace std;
using namespace aura;

ObjClass::ObjClass(Object *next, MemoryManager *mm, ObjString *name)
:   Object(next, ObjectType::CLASS),
    name(name),
    methods(mm)
{ }