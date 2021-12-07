#include "virtualmachine.ih"

bool VirtualMachine::call(ObjClosure *closure, int arg_count)
{
    // calculate free_stack
    size_t free_stack = d_stack_capacity - size_t(d_stack_top - d_stack);
    if (free_stack < closure->function->chunk.stack_requirement())
        grow_stack();

    if (d_frame_count == d_frame_capacity)
        grow_callstack();

    ObjFunction *function = closure->function;

    if (arg_count != function->arity)
    {
        runtime_error(("Expected "s + std::to_string(function->arity) + " arguments but got " + std::to_string(arg_count) + ".").c_str());
        return false;
    }
    
    d_frames[d_frame_count++] = 
    {
        closure,
        function,
        function->chunk.code(),
        d_stack_top - arg_count - 1
    };
    return true;
}