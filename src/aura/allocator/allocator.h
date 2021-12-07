#ifndef AURA_ALLOCATOR_H
#define AURA_ALLOCATOR_H

#include "../memorymanager/memorymanager.h"

namespace aura
{
    
    template <typename Type>
    class Allocator
    {
        MemoryManager *d_vm;

        public:
            // type traits
            using value_type = Type;
            using size_type = size_t;
            using difference_type = std::ptrdiff_t;
            using propagate_on_container_move_assignment = std::true_type;
            using is_always_equal = std::false_type;

            // member functions
            Allocator(MemoryManager *vm);

            [[nodiscard]] constexpr Type *allocate(size_t num);
            constexpr void deallocate(Type *ptr, size_t num);
    };

    template <typename Type>
    constexpr bool operator==(Allocator<Type> const &lhs, Allocator<Type> const &rhs)
    {
        return lhs.d_vm == rhs.d_vm;
    }

    template <typename Type1, typename Type2>
    constexpr bool operator==(Allocator<Type1> const &, Allocator<Type2> const &)
    {
        return false;
    }

}

#include "allocator.f"

#endif