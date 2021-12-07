#include "valuetable.ih"

bool ValueTable::get(ObjString *key, Value *value)
{
    if (d_count == 0)
        return false;
    
    Entry *entry = find_entry(key);

    if (entry->key != nullptr)
    {
        *value = entry->value;
        return true;
    }

    return false;
}