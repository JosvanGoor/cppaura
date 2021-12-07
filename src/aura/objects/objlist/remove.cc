#include "objlist.ih"

Value ObjList::remove(Object *obj, size_t num, Value *values, NativeInterface *ni)
{
    ObjList *list = reinterpret_cast<ObjList*>(obj);

    if (num != 1)
    {
        ni->native_error("ObjList.remove expected exactly 1 argument");
        return {};
    }

    if (values[0].type != ValueType::INT)
    {
        ni->native_error("ObjList.remove expects integer argument");
        return {};
    }

    int64_t index = values[0].as.integer;
    if (index < 0 || index >= int64_t(list->list.size()))
    {
        ni->native_error("ObjList.remove: to be removed index out of range.");
        return {};
    }

    list->list.erase(list->list.begin() + index);
    return {};
}