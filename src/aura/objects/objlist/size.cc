#include "objlist.ih"

Value ObjList::size(Object *obj, size_t num, [[maybe_unused]]Value *values, NativeInterface *ni)
{
    // we assume typing is correct
    if (num != 0)
    {
        ni->native_error("ObjList.size expects 0 arguments.");
        return {};
    }
    
    return int64_t(reinterpret_cast<ObjList*>(obj)->list.size());
}