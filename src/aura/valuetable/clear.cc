#include "valuetable.ih"

void ValueTable::clear()
{
    d_mm->deallocate(d_entries, sizeof(Entry) * d_capacity);
    d_entries = nullptr;
    d_count = 0;
    d_capacity = 0;
    d_mask = 0;
}