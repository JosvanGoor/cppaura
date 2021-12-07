#include "objlist.ih"

Value ObjList::append(Object *obj, size_t num, Value *values, NativeInterface *ni)
{
    ObjList *list = reinterpret_cast<ObjList*>(obj);

    if (num != 1)
    {
        ni->native_error("ObjList.append expected exactly 1 argument");
        return {};
    }

    list->list.push_back(values[0]);
    return {};
}