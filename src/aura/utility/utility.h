#ifndef UTILITY_AURA_H
#define UTILITY_AURA_H

#include <cstddef>
#include <cstdint>

namespace aura
{

    char *read_file(char const *filename);
    uint32_t hash_string(char const *chars, size_t length);
}

#endif