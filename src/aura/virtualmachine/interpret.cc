#include "virtualmachine.ih"

#include <chrono>

InterpretResult VirtualMachine::interpret(char *source)
{
    Compiler compiler{this};
    
    // we hotswap the garbage collect function because the compiler might need to
    // mark roots during compiling.
    d_collect_callback = bind(&Compiler::mark_roots, &compiler);
    ObjFunction *function = compiler.compile(source);
    d_collect_callback = bind(&VirtualMachine::collect_garbage, this);

    if (function == nullptr)
        return InterpretResult::COMPILE_ERROR;

    push(function);
    ObjClosure *closure = allocate_object<ObjClosure>(this, function);
    pop();
    push(closure);
    call_value(closure, 0);
    
    return run();
}