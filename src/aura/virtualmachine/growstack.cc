#include "virtualmachine.ih"

void VirtualMachine::grow_stack()
{
    size_t new_size = d_stack_capacity == 0 ? (64 * 256) : d_stack_capacity * 2;
    cout << ">> Growing stack from " << d_stack_capacity << " to " << new_size << "<<\n";

    Value *new_stack = new Value[new_size];
    // copy over old values
    copy(d_stack, d_stack_top, new_stack);

    // now we need to reset all the stack pointers that are still active,
    // rebase open upvalues
    rebase_open_upvalues(new_stack);

    // reset callframe stack base
    rebase_callframe_stacks(new_stack);

    d_stack_top = &new_stack[d_stack_top - d_stack]; // set new stack top.
    delete[] d_stack;

    d_stack = new_stack;
    d_stack_capacity = new_size;
}