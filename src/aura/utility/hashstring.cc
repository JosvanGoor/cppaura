#include "utility.ih"

uint32_t aura::hash_string(char const *chars, size_t length)
{
    uint32_t hash = 2166136261u;

    for (size_t idx = 0; idx < length; ++idx)
    {
        hash ^= chars[idx];
        hash *= 16777619;
    }

    return hash;
}