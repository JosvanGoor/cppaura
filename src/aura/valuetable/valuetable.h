#ifndef AURA_VALUETABLE_H
#define AURA_VALUETABLE_H

#include "../value/value.h"
#include "../memorymanager/memorymanager.h"

/*
    The ValueTable is a hashmap implementation specific for storing
    member values or globals. Key/Value pair ar ObjString* // Value.
    It also contains functions used by the VM for string interning.
    This is concretely different from the (future) dict implementation which will
    use Value // Value pairs.
*/

namespace aura
{
    // forward decl
    class ObjString;
    class VirtualMachine;

    class ValueTable
    {
        struct Entry;
        static constexpr double max_load = 0.5;

        size_t d_mask;
        size_t d_count;
        size_t d_capacity;
        Entry *d_entries;
        MemoryManager *d_mm;

        public:
            ValueTable(MemoryManager *mm);
            ~ValueTable();

            bool set(ObjString *key, Value value);
            bool get(ObjString *key, Value *value);
            bool remove(ObjString *key);
            void clear();

            // gc helper
            void mark_contents(VirtualMachine *vm);
            void remove_white();

            // util
            void add_all(ValueTable const &other);
            ObjString *find_string(char const *chars, size_t length, uint32_t hash);

            // debugging
            void print_occupance();

        private:
            void grow();
            Entry *find_entry(ObjString *key);
    };

    struct ValueTable::Entry
    {
        ObjString *key;
        Value value;
    };

}



#endif