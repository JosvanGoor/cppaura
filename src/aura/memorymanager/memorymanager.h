#ifndef AURA_MEMORYMANAGER_H
#define AURA_MEMORYMANAGER_H

#include <cstddef>
#include <cstdlib>
#include <functional>
#include <utility>

// #define DEBUG_STRESS_GC
#define DEBUG_LOG_GC
#define GC_HEAP_GROW_FACTOR 2

namespace aura
{

    class Object;
    using GcCallback = std::function<void()>;

    class MemoryManager
    {
        protected:
            Object *d_objects;
            size_t d_next_collect;
            size_t d_bytes_allocated;
            GcCallback d_collect_callback;

        public:
            MemoryManager();
            ~MemoryManager();

            // allocation for raw memory
            [[nodiscard]] void *allocate(size_t numbytes);
            void deallocate(void *ptr, size_t numbytes);

            // templated object creator and destroyer
            template <typename Obj, typename ...Args>
            [[nodiscard]] Obj *allocate_object(Args ...args);
            void deallocate_object(Object *object);

            // utility
            void free_all_objects();

        private:
            template <typename Obj>
            void destroy_and_free(Obj *obj);
    };

}

#include "allocateobject.f"
#include "destroyandfree.f"

#endif