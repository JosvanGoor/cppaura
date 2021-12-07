#include "virtualmachine.ih"

/* Some debugging flags */
// #define DEBUG_TRACE_EXECUTION

InterpretResult VirtualMachine::run()
{
    CallFrame *frame = &d_frames[d_frame_count - 1];

    /* I know defines are bad but they clean up the code real nice */
    #define READ_BYTE() (*frame->ip++)
    #define READ_SHORT() (frame->ip += 2, uint16_t((frame->ip[-2] << 8) | frame->ip[-1]))
    #define READ_CONSTANT() (frame->function->chunk.constant(READ_BYTE()))
    #define READ_CONSTANT_16() (frame->function->chunk.constant(READ_SHORT()))
    #define READ_STRING() (reinterpret_cast<ObjString*>(READ_CONSTANT().as.object))
    #define READ_STRING_16() (reinterpret_cast<ObjString*>(READ_CONSTANT_16().as.object))

    while (true)
    {
        #ifdef DEBUG_TRACE_EXECUTION
            cout << "\n          ";
            for (Value *slot = d_stack; slot < d_stack_top; ++slot)
                cout << "[ " << *slot << " ]";
            cout << "\n";
            disassemble_instruction(frame->function->chunk, int(frame->ip - frame->function->chunk.code()));
        #endif

        uint8_t instruction = READ_BYTE();
        switch (instruction)
        {
            /*
                Constants opcodes
            */
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }

            case OP_CONSTANT_16:
            {
                Value constant = READ_CONSTANT_16();
                push(constant);
                break;
            }

            case OP_ONE:        push(int64_t(1)); break;
            case OP_ZERO:       push(int64_t(0)); break;
            case OP_NIL:        push(Value{}); break;
            case OP_FALSE:      push(false); break;
            case OP_TRUE:       push(true); break;

            /*
                Setting and getting variables.
            */
            case OP_DEFINE_GLOBAL:
            {
                ObjString *name = READ_STRING();
                d_globals.set(name, peek());
                pop();
                break;
            }
            case OP_DEFINE_GLOBAL_16:
            {
                ObjString *name = READ_STRING_16();
                d_globals.set(name, peek());
                pop();
                break;
            }

            case OP_GET_GLOBAL:
            {
                ObjString *name = READ_STRING();
                Value value;
                if (!d_globals.get(name, &value))
                {
                    runtime_error((string{"Undefined variable '"} + string{name->chars} + "'.").c_str());
                    return InterpretResult::RUNTIME_ERROR;
                }
                push(value);
                break;
            }
            case OP_GET_GLOBAL_16:
            {
                ObjString *name = READ_STRING_16();
                Value value;
                if (!d_globals.get(name, &value))
                {
                    runtime_error((string{"Undefined variable '"} + string{name->chars} + "'.").c_str());
                    return InterpretResult::RUNTIME_ERROR;
                }
                push(value);
                break;
            }

            case OP_SET_GLOBAL:
            {
                ObjString *name = READ_STRING();
                if (d_globals.set(name, peek()))
                {
                    d_globals.remove(name);
                    runtime_error((string{"Undefined variable '"} + string{name->chars} + "'.").c_str());
                    return InterpretResult::RUNTIME_ERROR;
                }
                break;
            }
            case OP_SET_GLOBAL_16:
            {
                ObjString *name = READ_STRING_16();
                if (d_globals.set(name, peek()))
                {
                    d_globals.remove(name);
                    runtime_error((string{"Undefined variable '"} + string{name->chars} + "'.").c_str());
                    return InterpretResult::RUNTIME_ERROR;
                }
                break;
            }

            case OP_GET_LOCAL:
            {
                uint8_t slot = READ_BYTE();
                push(frame->slots[slot]);
                break;
            }
            case OP_GET_LOCAL_16:
            {
                uint16_t slot = READ_SHORT();
                push(frame->slots[slot]);
                break;
            }

            case OP_SET_LOCAL:
            {
                uint8_t slot = READ_BYTE();
                frame->slots[slot] = peek();
                break;
            }
            case OP_SET_LOCAL_16:
            {
                uint16_t slot = READ_SHORT();
                frame->slots[slot] = peek();
                break;
            }

            case OP_GET_UPVALUE:
            {
                uint16_t slot = READ_SHORT();
                push(*frame->closure->upvalues[slot]->location);
                break;
            }

            case OP_SET_UPVALUE:
            {
                uint16_t slot = READ_SHORT();
                *frame->closure->upvalues[slot]->location = peek();
                break;
            }

            case OP_GET_PROPERTY:
            {
                if (!peek().is_obj_type(ObjectType::INSTANCE))
                {
                    runtime_error("Only instances have properties.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                ObjInstance *instance = reinterpret_cast<ObjInstance*>(peek().as.object);
                ObjString *name = READ_STRING();

                Value value;
                if (instance->fields.get(name, &value))
                {
                    peek() = value;
                    break;
                }

                if (!bind_method(instance->klass, name))
                    return InterpretResult::RUNTIME_ERROR;
                break;
            }
            case OP_GET_PROPERTY_16:
            {
                if (!peek().is_obj_type(ObjectType::INSTANCE))
                {
                    runtime_error("Only instances have properties.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                ObjInstance *instance = reinterpret_cast<ObjInstance*>(peek().as.object);
                ObjString *name = READ_STRING_16();

                Value value;
                if (instance->fields.get(name, &value))
                {
                    peek() = value;
                    break;
                }

                if (!bind_method(instance->klass, name))
                    return InterpretResult::RUNTIME_ERROR;
                break;
            }

            case OP_SET_PROPERTY:
            {
                if (!peek(1).is_obj_type(ObjectType::INSTANCE))
                {
                    runtime_error("Only instances have fields.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                ObjInstance *instance = reinterpret_cast<ObjInstance*>(peek(1).as.object);
                instance->fields.set(READ_STRING(), peek());

                Value value = pop();
                peek() = value;
                break;
            }
            case OP_SET_PROPERTY_16:
            {
                if (!peek(1).is_obj_type(ObjectType::INSTANCE))
                {
                    runtime_error("Only instances have fields.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                ObjInstance *instance = reinterpret_cast<ObjInstance*>(peek(1).as.object);
                instance->fields.set(READ_STRING_16(), peek());

                Value value = pop();
                peek() = value;
                break;
            }

            case OP_GET_SUPER:
            {
                ObjString *name = READ_STRING();
                ObjClass *superclass = reinterpret_cast<ObjClass*>(pop().as.object);
                if (!bind_method(superclass, name))
                    return InterpretResult::RUNTIME_ERROR;
                break;
            }
            case OP_GET_SUPER_16:
            {
                ObjString *name = READ_STRING_16();
                ObjClass *superclass = reinterpret_cast<ObjClass*>(pop().as.object);
                if (!bind_method(superclass, name))
                    return InterpretResult::RUNTIME_ERROR;
                break;
            }

            case OP_COMPOUND_PROPERTY:
            {
                ObjString *name = READ_STRING();
                if (!op_compound_property(name, READ_BYTE()))
                    return InterpretResult::RUNTIME_ERROR;
                break;
            }
            case OP_COMPOUND_PROPERTY_16:
            {
                ObjString *name = READ_STRING_16();
                if (!op_compound_property(name, READ_BYTE()))
                    return InterpretResult::RUNTIME_ERROR;
                break;
            }

            case OP_COMPOUND_SUBSCRIPT:
                if (!op_compound_subscript(READ_BYTE()))
                    return InterpretResult::RUNTIME_ERROR;
                break;

            /*
                Unary's
            */
            case OP_NEGATE:
            {
                switch(peek().type) 
                {
                    case ValueType::INT: peek().as.integer *= -1; break;
                    case ValueType::FLOAT: peek().as.floating *= -1; break;
                    default:
                        runtime_error("Operand must be int or float type.");
                        return InterpretResult::RUNTIME_ERROR;
                }
                break;
            }

            case OP_NOT:        
                push(is_falsey(pop()));
                break;

            /*
                Arythmic
            */
            case OP_ADD:
                if (!op_add()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_SUBSTRACT:
                if (!numeric_binary<minus<int64_t>, minus<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_MULTIPLY:
                if (!numeric_binary<multiplies<int64_t>, multiplies<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_DIVIDE:
                if (!numeric_binary<divides<int64_t>, divides<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_MODULO:
                if (!op_modulo()) return InterpretResult::RUNTIME_ERROR;
                break;

            /*
                Comparison
            */
            case OP_EQUAL:
                op_equal();
                break;
            case OP_NOT_EQUAL:
                op_not_equal();
                break;
            case OP_GREATER:
                if (!numeric_binary<greater<int64_t>, greater<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_GREATER_EQUAL:
                if (!numeric_binary<greater_equal<int64_t>, greater_equal<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_LESS:
                if (!numeric_binary<less<int64_t>, less<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;
            case OP_LESS_EQUAL:
                if (!numeric_binary<less_equal<int64_t>, less_equal<double>>()) return InterpretResult::RUNTIME_ERROR;
                break;

            /*
                Jumps
            */
            case OP_JUMP:
            {
                uint16_t offset = READ_SHORT();
                frame->ip += offset;
                break;
            }
            
            case OP_JUMP_IF_FALSE:
            {
                    uint16_t offset = READ_SHORT();
                    if (is_falsey(peek()))
                        frame->ip += offset;
                    break;
            }

            case OP_JUMP_IF_TRUE:
            {
                    uint16_t offset = READ_SHORT();
                    if (!is_falsey(peek()))
                        frame->ip += offset;
                    break;
            }

            case OP_LOOP:
            {
               uint16_t offset = READ_SHORT();
               frame->ip -= offset;
               break;
            }

            case OP_BREAK:
            {
                uint16_t offset = READ_SHORT();
                pop(READ_SHORT());
                close_upvalues(d_stack_top);
                frame->ip += (offset - 2); // -2 cause we already read 2 bytes
                break;
            }

            case OP_CONTINUE:
            {
                uint16_t offset = READ_SHORT();
                pop(READ_SHORT()); // pop all locals.
                close_upvalues(d_stack_top); // close if required.

                frame->ip -= (offset + 2); // +2 to offset the pop operand.
                break;
            }

            /*
                Calls
            */
            case OP_CALL:
            {
                int arg_count = READ_BYTE();
                if (!call_value(peek(arg_count), arg_count))
                    return InterpretResult::RUNTIME_ERROR;
                
                frame = &d_frames[d_frame_count - 1];
                break;
            }

            case OP_INVOKE:
            {
                ObjString *method = READ_STRING();
                int arg_count = READ_BYTE();
                if (!invoke(method, arg_count))
                    return InterpretResult::RUNTIME_ERROR;
                frame = &d_frames[d_frame_count - 1];
                break;
            }
            case OP_INVOKE_16:
            {
                ObjString *method = READ_STRING_16();
                int arg_count = READ_BYTE();
                if (!invoke(method, arg_count))
                    return InterpretResult::RUNTIME_ERROR;
                frame = &d_frames[d_frame_count - 1];
                break;
            }
            
            case OP_SUPER_INVOKE:
            {
                ObjString *method = READ_STRING();
                int arg_count = READ_BYTE();
                ObjClass *superclass = reinterpret_cast<ObjClass*>(pop().as.object);
                if (!invoke_from_class(superclass, method, arg_count))
                    return InterpretResult::RUNTIME_ERROR;
                frame = &d_frames[d_frame_count - 1];
                break;
            }
            case OP_SUPER_INVOKE_16:
            {
                ObjString *method = READ_STRING_16();
                int arg_count = READ_BYTE();
                ObjClass *superclass = reinterpret_cast<ObjClass*>(pop().as.object);
                if (!invoke_from_class(superclass, method, arg_count))
                    return InterpretResult::RUNTIME_ERROR;
                frame = &d_frames[d_frame_count - 1];
                break;
            }
            /*
                Special Datatypes
            */
            case OP_MAKE_LIST:
            {
                int entries = READ_SHORT();
                ObjList *list = allocate_object<ObjList>(this);
                push(list); // for GC
                
                list->copy_from(d_stack_top - 1 - entries, entries);
                
                pop(entries); // pop entries off stack
                peek() = list; // put list back, now on top.
                
                break;
            }

            case OP_GET_SUBSCRIPT:
            {
                if (peek().type != ValueType::INT)
                {
                    runtime_error("List index must be an integer.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                int index = pop().as.integer;
                
                if (!peek().is_obj_type(ObjectType::LIST))
                {
                    runtime_error("Only lists are subscriptable.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                ObjList *list = reinterpret_cast<ObjList*>(peek().as.object);
                
                if (index < 0 || list->list.size() <= size_t(index))
                {
                    runtime_error("Index out of bounds.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                peek() = list->list[index];
                break;
            }
            case OP_SET_SUBSCRIPT:
            {
                if (!peek(2).is_obj_type(ObjectType::LIST))
                {
                    runtime_error("Only lists are subscriptable.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                if (peek(1).type != ValueType::INT)
                {
                    runtime_error("List index must be an integer.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                ObjList *list = reinterpret_cast<ObjList*>(peek(2).as.object);
                int index = peek(1).as.integer;
                if (index < 0 || list->list.size() <= size_t(index))
                {
                    runtime_error("Index out of bounds.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                
                list->list[index] = peek();
                peek(2) = peek();
                pop(2);
                break;
            }

            /*
                VM constructs
             */
            case OP_CLASS:
            {
                push(allocate_object<ObjClass>(this, READ_STRING()));
                break;
            }
            case OP_CLASS_16:
            {
                push(allocate_object<ObjClass>(this, READ_STRING_16()));
                break;
            }

            case OP_INHERIT:
            {
                Value superclass = peek(1);

                if (!superclass.is_obj_type(ObjectType::CLASS))
                {
                    runtime_error("Superclass must be a class.");
                    return InterpretResult::RUNTIME_ERROR;
                }

                ObjClass *subclass = reinterpret_cast<ObjClass*>(peek().as.object);
                subclass->methods.add_all(reinterpret_cast<ObjClass*>(superclass.as.object)->methods);
                pop(); // subclass
                break;
            }

            case OP_METHOD:
                define_method(READ_STRING());
                break;
            case OP_METHOD_16:
                define_method(READ_STRING_16());
                break;

            case OP_CLOSURE:
            {
                ObjFunction *function = reinterpret_cast<ObjFunction*>(READ_CONSTANT().as.object);
                ObjClosure *closure = allocate_object<ObjClosure>(this, function);
                push(closure);
                
                for (int idx = 0; idx < closure->upvalue_count; ++idx)
                {
                    uint8_t is_local = READ_BYTE();
                    uint16_t index = READ_SHORT();
                    if (is_local)
                        closure->upvalues[idx] = capture_upvalue(frame->slots + index);
                    else
                        closure->upvalues[idx] = frame->closure->upvalues[idx];
                }
                break;
            }
            case OP_CLOSURE_16:
            {
                ObjFunction *function = reinterpret_cast<ObjFunction*>(READ_CONSTANT_16().as.object);
                ObjClosure *closure = allocate_object<ObjClosure>(this, function);
                push(closure);

                for (int idx = 0; idx < closure->upvalue_count; ++idx)
                {
                    uint8_t is_local = READ_BYTE();
                    uint16_t index = READ_SHORT();
                    if (is_local)
                        closure->upvalues[idx] = capture_upvalue(frame->slots + index);
                    else
                        closure->upvalues[idx] = frame->closure->upvalues[idx];
                }
                break;
            }

            case OP_CLOSE_UPVALUES:
            {
                close_upvalues(d_stack_top);
                break;
            }

            case OP_POP:
                pop();
                break;
            case OP_POP_N:
                pop(READ_BYTE());
                break;
            case OP_POP_N_16:
                pop(READ_SHORT());
                break;

            case OP_PRINT:
                cout << pop() << "\n";
                break;

            case OP_RETURN:
            {
                Value result = pop();
                close_upvalues(frame->slots); // closes all parameters as upvalues.
                --d_frame_count;

                if (d_frame_count == 0)
                {
                    pop();
                    return InterpretResult::OK;
                }

                d_stack_top = frame->slots;
                push(result);

                frame = &d_frames[d_frame_count - 1];
                break;
            }

            /*
                Unreachable safeguard.
            */
            default:
                runtime_error("Unknown opcode.");
                return InterpretResult::RUNTIME_ERROR;
        }
    }

    /* But we clean up after ourselves */
    #undef READ_BYTE
    #undef READ_SHORT
    #undef READ_CONSTANT
    #undef READ_CONSTANT_16
    #undef READ_STRING
    #undef READ_STRING_16
}