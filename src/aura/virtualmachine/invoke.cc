#include "virtualmachine.ih"

bool VirtualMachine::invoke(ObjString *name, int arg_count)
{
    Value receiver = peek(arg_count);

    if (!receiver.is_obj_type(ObjectType::INSTANCE))
    {
        // maybe it is a native type with methods.
        if (invoke_native(name, arg_count)) 
            return true;
        
        return false;
    }

    // happy path yay!

    ObjInstance *instance = reinterpret_cast<ObjInstance*>(receiver.as.object);
    
    Value value;
    if (instance->fields.get(name, &value))
    {
        d_stack_top[-arg_count - 1] = value;
        return call_value(value, arg_count);
    }
    
    return invoke_from_class(instance->klass, name, arg_count);
}