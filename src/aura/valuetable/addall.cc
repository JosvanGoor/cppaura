#include "valuetable.ih"

void ValueTable::add_all(ValueTable const &other)
{
    for (size_t idx = 0; idx < other.d_capacity; ++idx)
    {
        Entry *entry = &other.d_entries[idx];
        if (entry->key != nullptr)
            set(entry->key, entry->value);
    }
}