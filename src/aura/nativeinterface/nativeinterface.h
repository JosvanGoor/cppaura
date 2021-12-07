#ifndef AURA_NATIVE_INTERFACE_H
#define AURA_NATIVE_INTERFACE_H

#include "../memorymanager/memorymanager.h"
#include "../valuetable/valuetable.h"

namespace aura
{

    /*
        Interface passed to native functions / methods. Allow them to flag for errors.
    */

    class NativeInterface
    {
        protected:
            bool d_native_ok = true; // flags errors in native functions.

            // needs setup in VM
            ValueTable d_list_methods;

            NativeInterface(MemoryManager *mm);

        public:
            void native_error(char const *message);
    };

}

#endif