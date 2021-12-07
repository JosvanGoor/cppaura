#include "objnativefunction.h"

using namespace std;
using namespace aura;

ObjNativeFunction::ObjNativeFunction(Object *next, NativeFunction func)
:   Object(next, ObjectType::NATIVE_FUNCTION),
    function(func)
{
    
}