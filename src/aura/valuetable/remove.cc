#include "valuetable.ih"

bool ValueTable::remove(ObjString *key)
{
    if (d_count == 0)
        return false;

    Entry *entry = find_entry(key);
    if (entry->key == nullptr)
        return false;

    entry->key = nullptr;
    entry->value = true;

    return true;
}