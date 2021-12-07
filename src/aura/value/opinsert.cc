#include "value.ih"

ostream &aura::operator<<(ostream &out, Value const &val)
{
    out << val.to_string();
    return out;
}