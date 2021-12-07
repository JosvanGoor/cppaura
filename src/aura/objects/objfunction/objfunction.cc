#include "objfunction.h"

using namespace std;
using namespace aura;

ObjFunction::ObjFunction(Object *next, MemoryManager *vm)
:   Object(next, ObjectType::FUNCTION),
    arity(0),
    upvalue_count(0),
    chunk(vm),
    name(nullptr)
{
}