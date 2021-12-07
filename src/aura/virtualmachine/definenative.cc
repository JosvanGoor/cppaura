#include "virtualmachine.ih"

void VirtualMachine::define_native(char const *name, NativeFunction func)
{
    push(copy_string(name, strlen(name)));
    push(allocate_object<ObjNativeFunction>(func));
    d_globals.set(reinterpret_cast<ObjString*>(peek(1).as.object), peek(0));
    pop();
    pop();
}