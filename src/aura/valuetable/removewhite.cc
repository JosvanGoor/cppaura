#include "valuetable.ih"

void ValueTable::remove_white()
{
    for (size_t idx = 0; idx < d_capacity; ++idx)
    {
        Entry *entry = &d_entries[idx];
        if (entry->key != nullptr && !entry->key->is_marked)
            remove(entry->key);
    }
}