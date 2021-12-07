#include "chunk.ih"

size_t Chunk::write_constant(Value value)
{
    

    // check if this constant already exists somewhere
    for (size_t idx = 0; idx < d_constants.size(); ++idx)
    {
        if (d_constants[idx] == value)
            return idx;
    }

    // if it doesnt exist, store it
    d_constants.push_back(value);
    return d_constants.size() - 1;
}