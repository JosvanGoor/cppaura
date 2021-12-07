#include "objlist.ih"

Value ObjList::concat(Object *obj, size_t num, Value *values, NativeInterface *ni)
{
    ObjList *list = reinterpret_cast<ObjList*>(obj);

    if (num != 1)
    {
        ni->native_error("ObjList.concat expected exactly 1 argument");
        return {};
    }

    if (!values[0].is_obj_type(ObjectType::LIST))
    {
        ni->native_error("ObjList.concat expects a list as argument.");
        return {};
    }

    ObjList *toadd = reinterpret_cast<ObjList*>(values[0].as.object);
    list->list.insert(list->list.end(), toadd->list.begin(), toadd->list.end());

    return {};   
}