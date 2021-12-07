#include "virtualmachine.ih"

void VirtualMachine::blacken_object(Object *object)
{
    switch(object->type)
    {
        case ObjectType::NATIVE_FUNCTION:   [[fallthrough]];
        case ObjectType::NATIVE_METHOD:     [[fallthrough]];
        case ObjectType::STRING:
            break;

        case ObjectType::BOUND_METHOD:
        {
            ObjBoundMethod *bound = reinterpret_cast<ObjBoundMethod*>(object);
            mark_value(bound->receiver);
            mark_object(bound->method);
            break;
        }
        
        case ObjectType::CLASS:
        {
            ObjClass *klass = reinterpret_cast<ObjClass*>(object);
            mark_object(klass->name);
            klass->methods.mark_contents(this);
            break;
        }

        case ObjectType::CLOSURE:
        {
            ObjClosure *closure = reinterpret_cast<ObjClosure*>(object);
            mark_object(closure->function);
            for (int idx = 0; idx < closure->upvalue_count; ++idx)
                mark_object(closure->upvalues[idx]);
            break;
        }

        case ObjectType::FUNCTION:
        {
            ObjFunction *function = reinterpret_cast<ObjFunction*>(object);
            mark_object(function->name);
            mark_array(function->chunk.constants());
            break;
        }

        case ObjectType::INSTANCE:
        {
            ObjInstance *instance = reinterpret_cast<ObjInstance*>(object);
            mark_object(instance->klass);
            instance->fields.mark_contents(this);
            break;
        }

        case ObjectType::LIST:
        {
            ObjList *list = reinterpret_cast<ObjList*>(object);
            for (size_t idx = 0; idx < list->list.size(); ++idx)
                mark_value(list->list[idx]);
            break;
        }

        case ObjectType::UPVALUE:
            mark_value(reinterpret_cast<ObjUpvalue*>(object)->closed);
            break;
    }
}
