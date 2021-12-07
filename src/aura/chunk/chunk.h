#ifndef AURA_CHUNK_H
#define AURA_CHUNK_H

#include <cstdint>
#include <vector>

#include "../allocator/allocator.h"
#include "../value/value.h"
#include "../memorymanager/memorymanager.h"

namespace aura
{
    class Chunk
    {
        struct LineInfo;

        size_t d_required_stack;
        std::vector<uint8_t, Allocator<uint8_t>> d_code;
        std::vector<LineInfo, Allocator<LineInfo>> d_line_info;
        std::vector<Value, Allocator<Value>> d_constants;

        public:
            Chunk(MemoryManager *vm);

            void write(uint8_t byte, size_t line);
            void write_line(size_t line);
            size_t write_constant(Value value);

            uint8_t *code();
            uint8_t const *code() const;
            Value const &constant(size_t index) const;
            bool consecutive_line(size_t index) const;
            size_t instruction_line(size_t index) const;
            size_t code_length() const;

            size_t stack_requirement() const;
            void set_stack_requirement(size_t required);

            std::vector<Value, Allocator<Value>> &constants();

        private:
            Chunk(Chunk const &);
            Chunk &operator=(Chunk const &);
    };

    struct Chunk::LineInfo
    {
        size_t line;
        size_t start_index;
        size_t last_index;
    };

}

#endif