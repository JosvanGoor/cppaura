#include "chunk.ih"

#include <iostream> // _DBG

void Chunk::write_line(size_t line)
{
    if (d_line_info.empty() || d_line_info.back().line != line)
        d_line_info.push_back({line, d_code.size(), d_code.size()});
    else
        d_line_info.back().last_index = d_code.size();
}