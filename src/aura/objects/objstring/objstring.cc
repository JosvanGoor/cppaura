#include "objstring.h"

#include "../../utility/utility.h"
#include "../../virtualmachine/virtualmachine.h"

using namespace std;

namespace aura
{

    ObjString::ObjString(Object *next, char *chars, size_t length, uint32_t hash)
    :   Object(next, ObjectType::STRING),
        hash(hash),
        length(length),
        chars(chars)
    { }

}