#include "valuetable.ih"

ValueTable::Entry *ValueTable::find_entry(ObjString *key)
{
    uint32_t index = key->hash & d_mask;
    Entry *tombstone = nullptr;

    while (true)
    {
        Entry *entry = &d_entries[index];

        if (entry->key == nullptr)
        {
            if (entry->value.type == ValueType::NIL) // empty entry
                return tombstone != nullptr ? tombstone : entry;
            else // we found tombstone
            {
                if (tombstone == nullptr)
                    tombstone = entry;
            }
        }
        else if (entry->key == key)
        {
            return entry;
        }

        index = (index + 1) & d_mask;
    }
}