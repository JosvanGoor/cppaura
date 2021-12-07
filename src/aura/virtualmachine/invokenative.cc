#include "virtualmachine.ih"

bool VirtualMachine::invoke_native(ObjString *name, int arg_count)
{
    Value receiver = peek(arg_count);
    if (receiver.type != ValueType::OBJECT)
    {
        runtime_error("Caller doesn't have methods.");   
        return false;
    }

    switch(receiver.as.object->type)
    {
        case ObjectType::LIST:
        {
            Value method_val;
            if (d_list_methods.get(name, &method_val))
            {
                ObjNativeMethod *method = reinterpret_cast<ObjNativeMethod*>(method_val.as.object);
                Value result = method->method(receiver.as.object, arg_count, d_stack_top - arg_count, this);
                d_stack_top -= arg_count + 1;
                push(result);

                if (!d_native_ok)
                {
                    runtime_error(nullptr);
                    return false;
                }
                return true;
            }
            runtime_error(("Undefined property '"s + name->chars + "'.").c_str());
            return false;
        }

        default:
            runtime_error("Caller doesn't have methods.");
            return false;
    }
}