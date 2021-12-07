#include "virtualmachine.ih"


VirtualMachine::VirtualMachine()
:   MemoryManager(),
    NativeInterface(this),
    d_chunk(nullptr),
    d_ip(nullptr),
    d_strings(this),
    d_globals(this),
    d_open_upvalues(nullptr),
    d_stack(nullptr),
    d_stack_top(nullptr),
    d_stack_capacity(0),
    d_frame_count(0),
    d_frame_capacity(0),
    d_frames(nullptr),
    d_gray_count(0),
    d_gray_capacity(0),
    d_gray_stack(nullptr)
{
    grow_stack();
    grow_callstack();
    
    reset_stack();
    
    // collect callback
    d_collect_callback = bind(&VirtualMachine::collect_garbage, this);

    // define native functions
    define_native("clock", native_clock);
    
    // some debug stuff
    auto fgc = [&]([[maybe_unused]] size_t num, [[maybe_unused]] Value *val, [[maybe_unused]] NativeInterface *nn)
    {
        cout << "[Manual trigger] ";
        collect_garbage();
        return Value{};
    };
    define_native("force_gc", fgc);

    setup_objlist_methods();
}