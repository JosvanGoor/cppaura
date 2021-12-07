#include "objclosure.h"

using namespace std;
using namespace aura;

ObjClosure::ObjClosure(Object *next, MemoryManager *mm, ObjFunction *func)
:   Object(next, ObjectType::CLOSURE),
    function(func),
    upvalues(nullptr),
    upvalue_count(func->upvalue_count)
{ 
    upvalues = reinterpret_cast<ObjUpvalue**>(mm->allocate(sizeof(ObjUpvalue*) * upvalue_count));
    for (int idx = 0; idx < upvalue_count; ++idx)
    {
        upvalues[idx] = nullptr;
    }
}