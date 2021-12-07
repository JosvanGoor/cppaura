#include "virtualmachine.ih"

void VirtualMachine::define_method(ObjString *name)
{
    Value method = peek(0);
    ObjClass *klass = reinterpret_cast<ObjClass*>(peek(1).as.object);
    klass->methods.set(name, method);
    pop(); // pop closure of stack.
}