#include "chunk.ih"

/*
    Returns wether the instruction at this index is on the same line
    as the instrucion 1 index lower.
*/

bool Chunk::consecutive_line(size_t index) const
{
    for (size_t idx = 0; idx < d_line_info.size(); ++idx)
    {
        LineInfo const *info = &d_line_info[idx];
        if (index >= info->start_index && index <= info->last_index)
            return ((index - 1) >= info->start_index && (index - 1) <= info->last_index);
    }

    return false;
}