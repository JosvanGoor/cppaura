#include "objboundmethod.h"

using namespace std;
using namespace aura;

ObjBoundMethod::ObjBoundMethod(Object *next, Value receiver, ObjClosure *method)
:   Object(next, ObjectType::BOUND_METHOD),
    receiver(receiver),
    method(method)
{ }