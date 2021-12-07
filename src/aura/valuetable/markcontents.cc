#include "valuetable.ih"

void ValueTable::mark_contents(VirtualMachine *vm)
{
    for (size_t idx = 0; idx < d_capacity; ++idx)
    {
        Entry *entry = &d_entries[idx];
        vm->mark_object(entry->key);
        vm->mark_value(entry->value);
    }
}