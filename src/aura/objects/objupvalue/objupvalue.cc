#include "objupvalue.h"

using namespace std;
using namespace aura;

ObjUpvalue::ObjUpvalue(Object *next, Value *slot)
:   Object(next, ObjectType::UPVALUE),
    location(slot),
    closed(),
    next(nullptr)
{
    
}