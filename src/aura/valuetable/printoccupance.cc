#include "valuetable.ih"

#include <iomanip>

void ValueTable::print_occupance()
{
    for (size_t idx = 0; idx < d_capacity; ++idx)
    {
        cout << "[" << setw(3) << idx << "] ";

        Entry *entry = &d_entries[idx];
        if (entry->key == nullptr)
        {
            if (entry->value.type == ValueType::NIL)
                cout << "-\n";
            else
                cout << "RIP\n";
        }
        else
        {
            cout << "hash: " << setw(3) << (entry->key->hash & d_mask);
            cout << ". Key: '" << entry->key->chars << "' // Value: '";
            cout << entry->value.to_string() << "'\n";
        }
    }
}