#include "virtualmachine.ih"

bool VirtualMachine::call_value(Value callee, int arg_count)
{
    if (callee.type == ValueType::OBJECT)
    {
        switch (callee.as.object->type)
        {
            // case ObjectType::FUNCTION:
            //     return call(reinterpret_cast<ObjFunction*>(callee.as.object), arg_count);

            case ObjectType::BOUND_METHOD:
            {
                ObjBoundMethod *bound = reinterpret_cast<ObjBoundMethod*>(callee.as.object);
                d_stack_top[-arg_count - 1] = bound->receiver;
                return call(bound->method, arg_count);
            }

            case ObjectType::CLASS:
            {
                ObjClass *klass = reinterpret_cast<ObjClass*>(callee.as.object);
                d_stack_top[-arg_count - 1] = allocate_object<ObjInstance>(this, klass);
                
                Value initializer;
                if (klass->methods.get(klass->name, &initializer))
                    return call(reinterpret_cast<ObjClosure*>(initializer.as.object), arg_count);
                else if (arg_count != 0)
                {
                    runtime_error(("Expected 0 arguments but got "s + std::to_string(arg_count) + ".").c_str());
                    return false;
                }
                return true;
            }

            case ObjectType::CLOSURE:
                return call(reinterpret_cast<ObjClosure*>(callee.as.object), arg_count);

            case ObjectType::NATIVE_FUNCTION:
            {
                ObjNativeFunction *native = reinterpret_cast<ObjNativeFunction*>(callee.as.object);
                Value result = native->function(arg_count, d_stack_top - arg_count, this);
                d_stack_top -= arg_count + 1;
                push(result);
                
                if (!d_native_ok)
                {
                    runtime_error("Native Error flagged.");
                    return false;
                }
                return true;
            }

            default: break;
        }
    }

    runtime_error("Can only call functions and classes.");
    return false;
}