#include "virtualmachine.ih"

bool VirtualMachine::invoke_from_class(ObjClass *klass, ObjString *name, int arg_count)
{
    Value method;

    if (!klass->methods.get(name, &method))
    {
        runtime_error(("Undefined property "s + name->chars).c_str());
        return false;
    }

    return call(reinterpret_cast<ObjClosure*>(method.as.object), arg_count);
}