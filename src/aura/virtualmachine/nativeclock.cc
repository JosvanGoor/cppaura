#include "virtualmachine.ih"

#include <ctime>

Value aura::native_clock(size_t arg_count, [[maybe_unused]] Value *value, NativeInterface *ni)
{
    if (arg_count != 0)
        ni->native_error(("native_clock expected 0 arguments, got " + std::to_string(arg_count)).c_str());
    return (double(clock()) / CLOCKS_PER_SEC);
}