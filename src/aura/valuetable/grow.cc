#include "valuetable.ih"

void ValueTable::grow()
{
    size_t newcap = d_capacity < 8 ? 8 : (2 * d_capacity);

    Entry *entries = reinterpret_cast<Entry*>(d_mm->allocate(sizeof(Entry) * newcap));
    
    // empty init entries.
    for (size_t idx = 0; idx < newcap; ++idx)
        entries[idx] = {};

    Entry *old_entries = d_entries;
    size_t oldcap = d_capacity;

    d_capacity = newcap;
    d_mask = d_capacity - 1;
    d_entries = entries;
    d_count = 0;

    for (size_t idx = 0; idx < oldcap; ++idx)
    {
        Entry *entry = &old_entries[idx];
        if (entry->key == nullptr)
            continue;

        Entry *dest = find_entry(entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
        ++d_count;
    }
    
    if(old_entries)
        d_mm->deallocate(old_entries, sizeof(Entry) * oldcap);
}