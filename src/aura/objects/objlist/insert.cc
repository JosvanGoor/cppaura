#include "objlist.ih"

Value ObjList::insert(Object *obj, size_t num, Value *values, NativeInterface *ni)
{
    ObjList *list = reinterpret_cast<ObjList*>(obj);

    if (num != 2)
    {
        ni->native_error("ObjList.insert expects exactely 2 arguments");
        return {};
    }

    if (values[0].type != ValueType::INT)
    {
        ni->native_error("Index must be an integer");
        return {};
    }

    if (values[0].as.integer < 0 || size_t(values[0].as.integer) > list->list.size())
    {
        ni->native_error("Insertion index exeeds list dimensions.");
        return {};
    }

    list->list.insert(list->list.begin() + values[0].as.integer, values[1]);
    return {};
}