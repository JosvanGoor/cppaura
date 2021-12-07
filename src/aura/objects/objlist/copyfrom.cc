#include "objlist.ih"

void ObjList::copy_from(Value *value, size_t num)
{
    // list.reserve(num);

    for (size_t idx = 0; idx < num; ++idx)
        list.push_back(value[idx]);
}