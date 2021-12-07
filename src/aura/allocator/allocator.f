#include "allocator.h"

namespace aura
{
    template <typename Type>
    Allocator<Type>::Allocator(MemoryManager *vm)
    {
        d_vm = vm;
    }

    template <typename Type>
    [[nodiscard]] constexpr Type *Allocator<Type>::allocate(size_t num)
    {
        return reinterpret_cast<Type*>(d_vm->allocate(sizeof(Type) * num));
    }

    template <typename Type>
    constexpr void Allocator<Type>::deallocate(Type *ptr, size_t num)
    {
        d_vm->deallocate(ptr, sizeof(Type) * num);
    }

}