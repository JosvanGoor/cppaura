#include "memorymanager.ih"

void MemoryManager::deallocate_object(Object *object)
{
    switch(object->type)
    {
        case ObjectType::BOUND_METHOD:
        {
            destroy_and_free(reinterpret_cast<ObjBoundMethod*>(object));
            break;
        }

        case ObjectType::CLASS:
        {
            destroy_and_free(reinterpret_cast<ObjClass*>(object));
            break;
        }

        case ObjectType::CLOSURE:
        {
            ObjClosure *closure = reinterpret_cast<ObjClosure*>(object);
            deallocate(closure->upvalues, sizeof(ObjUpvalue*) * closure->upvalue_count);
            destroy_and_free(closure);
            break;
        }

        case ObjectType::FUNCTION:
        {
            ObjFunction *func = reinterpret_cast<ObjFunction*>(object);
            destroy_and_free(func);
            break;
        }

        case ObjectType::LIST:
        {
            ObjList *list = reinterpret_cast<ObjList*>(object);
            destroy_and_free(list);
            break;
        }

        case ObjectType::NATIVE_FUNCTION:
        {
            ObjNativeFunction *func = reinterpret_cast<ObjNativeFunction*>(object);
            destroy_and_free(func);
            break;
        }

        case ObjectType::NATIVE_METHOD:
        {
            ObjNativeMethod *method = reinterpret_cast<ObjNativeMethod*>(object);
            destroy_and_free(method);
            break;
        }

        case ObjectType::INSTANCE:
            destroy_and_free(reinterpret_cast<ObjInstance*>(object));
            break;

        case ObjectType::UPVALUE:
        {
            ObjUpvalue *upvalue = reinterpret_cast<ObjUpvalue*>(object);
            destroy_and_free(upvalue);
            break;
        }

        case ObjectType::STRING:
        {
            ObjString *str = reinterpret_cast<ObjString*>(object);
            deallocate(str->chars, str->length + 1);
            destroy_and_free(str);
            break;
        }

        default: break; // unreachable
    }
}