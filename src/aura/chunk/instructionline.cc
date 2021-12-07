#include "chunk.ih"

size_t Chunk::instruction_line(size_t index) const
{
    for (size_t idx = 0; idx < d_line_info.size(); ++idx)
    {
        LineInfo const *info = &d_line_info[idx];
        if (index >= info->start_index && index <= info->last_index)
            return info->line;
    }

    return -1;
}