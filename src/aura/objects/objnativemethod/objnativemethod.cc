#include "objnativemethod.h"

using namespace std;
using namespace aura;

ObjNativeMethod::ObjNativeMethod(Object *next, NativeMethod method)
:   Object(next, ObjectType::NATIVE_METHOD),
    method(method)
{ }