#include "virtualmachine.ih"

bool VirtualMachine::bind_method(ObjClass *klass, ObjString *name)
{
    Value method;

    if (!klass->methods.get(name, &method))
    {
        runtime_error(("Undefined property "s + name->chars).c_str());
        return false;
    }

    ObjBoundMethod *bound = allocate_object<ObjBoundMethod>
    (
        peek(),
        reinterpret_cast<ObjClosure*>(method.as.object)
    );
    peek() = bound;
    return true;
}