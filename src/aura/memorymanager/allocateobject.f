#include "memorymanager.h"

namespace aura
{

    template <typename Obj, typename ...Args>
    [[nodiscard]] Obj *MemoryManager::allocate_object(Args ...args)
    {
        void *data = allocate(sizeof(Obj));
        Obj *obj = new(data) Obj{d_objects, std::forward<Args>(args)...};
        d_objects = obj;

        return obj;
    }

}