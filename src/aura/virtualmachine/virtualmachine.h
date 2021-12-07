#ifndef AURA_VIRTUALMACHINE_H
#define AURA_VIRTUALMACHINE_H

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "../enums/interpretresult.h"
#include "../memorymanager/memorymanager.h"
#include "../nativeinterface/nativeinterface.h"
#include "../objects/objects.h"
#include "../value/value.h"
#include "../valuetable/valuetable.h"

namespace aura
{

    // forward decl.
    class Chunk;

    class VirtualMachine : public MemoryManager, public NativeInterface
    {
        // makes compiling more convenient
        friend class Compiler;
        
        // forward decl
        struct CallFrame;

        // member variables.
        Chunk *d_chunk;
        uint8_t const *d_ip; // Instruction pointer
        
        ValueTable d_strings;
        ValueTable d_globals;
        ObjUpvalue *d_open_upvalues;
        
        Value *d_stack;
        Value *d_stack_top;
        size_t d_stack_capacity;
        
        // call stack
        size_t d_frame_count;
        size_t d_frame_capacity;
        CallFrame *d_frames;

        // GC state
        size_t d_gray_count;
        size_t d_gray_capacity;
        Object **d_gray_stack;

        public:
            VirtualMachine();
            ~VirtualMachine();

            // Compilation & runtime
            InterpretResult interpret(char *source);
            InterpretResult run();
            
            void define_native(const char *name, NativeFunction func);

            // gc helpers
            void mark_value(Value value);
            void mark_object(Object *object);

            // Running
            void repl(); // command line interface.
            void run_file(char const *filename);

        private:
            // stack functions
            void pop(size_t num);
            Value pop();
            Value &peek();
            Value &peek(int distance);
            void push(Value const &value);
            void reset_stack();
            void swap_top(); // swaps top 2 values on stack.

            // call stuff
            bool call(ObjClosure *closure, int arg_count);
            bool call_value(Value callee, int arg_count);
            ObjUpvalue *capture_upvalue(Value *local);
            void close_upvalues(Value *last);

            // dynamic growth functions
            void grow_stack();
            void grow_callstack();
            void rebase_open_upvalues(Value *new_stack);
            void rebase_callframe_stacks(Value *new_stack);

            // garbage collection
            void blacken_object(Object *object);
            void collect_garbage();
            void grow_gray_stack();
            void mark_array(std::vector<Value, Allocator<Value>> &array);
            void mark_roots();
            void sweep();
            void trace_references();

            // methods stuff
            bool bind_method(ObjClass *klass, ObjString *name);
            void define_method(ObjString *name);
            bool invoke(ObjString *name, int arg_count);
            bool invoke_native(ObjString *name, int arg_count);
            bool invoke_from_class(ObjClass *klass, ObjString *name, int arg_count);

            // some native setup
            void setup_objlist_methods();

            // helpers
            bool is_falsey(Value const &value);
            void concatenate(); // concatenates string + ?
            // void concatenate(Value const &lhs, Value const &rhs);
            ObjString *take_string(char *chars, size_t length);
            ObjString *copy_string(char const *chars, size_t length);
            ObjString *allocate_string(char *chars, size_t length, uint32_t hash);
            
            // error functions
            void runtime_error(char const *message);

            // binary wrappers
            bool op_add();
            bool op_modulo();
            void op_equal();
            void op_not_equal();

            bool op_compound_property(ObjString *name, uint8_t opcode);
            bool op_compound_subscript(uint8_t opcode);

            // rest done with
            template <typename Operi, typename Operf>
            bool numeric_binary();
    };

    Value native_clock(size_t arg_count, Value *args, NativeInterface *ni);

    struct VirtualMachine::CallFrame
    {
        ObjClosure *closure = nullptr;
        ObjFunction *function = nullptr;
        uint8_t *ip = nullptr;
        Value *slots = nullptr;
    };
}

#include "numericbinary.f"

#endif