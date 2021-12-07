#include "objlist.ih"

Value ObjList::resize(Object *obj, size_t num, Value *values, NativeInterface *ni)
{
    ObjList *list = reinterpret_cast<ObjList*>(obj);

    if (num != 1 && num != 2)
    {
        ni->native_error("ObjList.resize expects 1 or 2 arguments.");
        return {};
    }

    if (values[0].type != ValueType::INT)
    {
        ni->native_error("ObjList.resize argument must be integer.");
        return {};
    }

    int64_t newsize = values[0].as.integer;
    if (newsize < 0)
    {
        ni->native_error("ObjList.resize: requested size can't be negative");
        return {};
    }

    if (size_t(newsize) < list->list.size())
        list->list.erase(list->list.begin() + newsize, list->list.end());
    else
    {
        if (num == 2)
            list->list.resize(newsize, values[1]);
        else 
            list->list.resize(newsize);
    }

    return {};
}