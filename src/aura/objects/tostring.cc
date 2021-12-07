#include "objects.ih"

#include <sstream>

static string ptr_str(void *ptr)
{
    stringstream out;
    out << ptr;
    return out.str();
}

string aura::to_string(Object *obj)
{
    switch(obj->type)
    {
        case ObjectType::BOUND_METHOD:
            return "<bm " + to_string(reinterpret_cast<ObjBoundMethod*>(obj)->method->function->name) + ">";

        case ObjectType::CLASS:
            return "<Class: " + string{reinterpret_cast<ObjClass*>(obj)->name->chars} + " @ " + ptr_str(obj) + ">";

        case ObjectType::CLOSURE:
        {
            ObjClosure *closure = reinterpret_cast<ObjClosure*>(obj);
            if (closure->function->name == nullptr)
                return "<cl script>";
            else return "<cl "s + to_string(closure->function->name) + ">";
        }

        case ObjectType::FUNCTION:
        {
            ObjFunction *func = reinterpret_cast<ObjFunction*>(obj);
            if (func->name == nullptr)
                return "<script>";
            else return "<fun "s + to_string(func->name) + ">";
        }
        
        case ObjectType::LIST:
        {
            ObjList *list = reinterpret_cast<ObjList*>(obj);
            stringstream ss;
            ss << "[";
            
            if (list->list.size() > 4)
            {
                ss << list->list[0] << ", " << list->list[1] << " ... ";
                ss << list->list[list->list.size() - 2] << ", " << list->list[list->list.size() - 1] << "]";
            }
            else
            {
                if (!list->list.empty())
                    ss << list->list[0].to_string();

                for (size_t idx = 1; idx < list->list.size(); ++idx)
                    ss << ", " << list->list[idx].to_string();
                ss << "]";
            }
            return ss.str();
        }

        case ObjectType::NATIVE_FUNCTION:
            return "<native fun>";

        case ObjectType::NATIVE_METHOD:
            return "<native method>";

        case ObjectType::INSTANCE:
        {
            ObjInstance *instance =reinterpret_cast<ObjInstance*>(obj);
            return to_string(instance->klass->name) + " instance";
        }

        case ObjectType::UPVALUE:
            return "upvalue";
        
        case ObjectType::STRING:
            return string{reinterpret_cast<ObjString*>(obj)->chars};
        
        default:
            return "_UNKNOWN_";
    }
}