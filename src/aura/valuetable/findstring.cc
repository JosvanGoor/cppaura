#include "valuetable.ih"

ObjString *ValueTable::find_string(char const *chars, size_t length, uint32_t hash)
{
    if (d_count == 0)
        return nullptr;

    uint32_t index = hash & d_mask;

    while (true)
    {
        Entry *entry = &d_entries[index];

        if (entry->key == nullptr)
        {
            // stop if we find non-tombstone entry
            if (entry->value.type == ValueType::NIL)
                return nullptr;
        }
        else if (entry->key->length == length
            && entry->key->hash == hash
            && memcmp(entry->key->chars, chars, length) == 0)
        {
            return entry->key; // Found it!
        }

        index = (index + 1) & d_mask;
    }
}