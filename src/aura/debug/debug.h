#ifndef AURA_DEBUG_H
#define AURA_DEBUG_H

#include <cstddef>
#include "../virtualmachine/virtualmachine.h"

namespace aura
{
    // forward decl
    class Chunk;

    void disassemble_chunk(Chunk const &chunk, char const *name);
    size_t disassemble_instruction(Chunk const &chunk, size_t offset);

}

#endif