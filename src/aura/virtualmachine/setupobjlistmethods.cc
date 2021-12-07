#include "virtualmachine.ih"

void VirtualMachine::setup_objlist_methods()
{
    auto add = [&](char const *name, auto funptr)
    {
        ObjString *str = copy_string(name, strlen(name));
        push(str);
        push(allocate_object<ObjNativeMethod>(funptr));
        d_list_methods.set(str, peek());
        pop(2);
    };

    add("size", &ObjList::size);
    add("append", &ObjList::append);
    add("concat", &ObjList::concat);
    add("remove", &ObjList::remove);
    add("resize", &ObjList::resize);
    add("insert", &ObjList::insert);
}