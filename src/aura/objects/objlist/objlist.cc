#include "objlist.ih"

ObjList::ObjList(Object *next, MemoryManager *mm)
:   Object(next, ObjectType::LIST),
    list(mm)
{

    

}