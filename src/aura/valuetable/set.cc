#include "valuetable.ih"

bool ValueTable::set(ObjString *key, Value value)
{
    // cout << "set: count // max = " << d_count << " // " << (d_capacity * max_load) << "\n";
    if ((d_count + 1) > (d_capacity * max_load))
        grow();

    Entry *entry = find_entry(key);

    bool is_new_key = entry->key == nullptr;

    // if not we revived a tombstone.
    if (is_new_key && entry->value.type == ValueType::NIL)
        ++d_count;

    entry->key = key;
    entry->value = value;

    return is_new_key;
}