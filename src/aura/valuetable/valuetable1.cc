#include "valuetable.ih"

ValueTable::ValueTable(MemoryManager *mm)
:   d_count(0),
    d_capacity(0),
    d_entries(nullptr),
    d_mm(mm)
{
    
}