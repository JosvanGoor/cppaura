#include "compiler.ih"

pair<int, size_t> Compiler::opcode_stack_effect(Chunk *chunk, size_t offset)
{
    auto read_short = [&]()
    {
        uint16_t val = chunk->code()[offset + 1] << 8;
        val |= chunk->code()[offset + 2];
        return val;
    };

    auto read_byte = [&]
    {
        return chunk->code()[offset + 1];
    };

    uint8_t opcode = chunk->code()[offset];
    switch (opcode)
    {
        case OP_CONSTANT:       return { 1, 2};
        case OP_CONSTANT_16:    return { 1, 3};

        case OP_ONE:            [[fallthrough]];
        case OP_ZERO:           [[fallthrough]];
        case OP_NIL:            [[fallthrough]];
        case OP_TRUE:           [[fallthrough]];
        case OP_FALSE:          return { 1, 1};

        // getting and setting
        case OP_DEFINE_GLOBAL:      return {-1, 2};
        case OP_DEFINE_GLOBAL_16:   return {-1, 3};
        case OP_GET_GLOBAL:         return { 1, 2};
        case OP_GET_GLOBAL_16:      return { 1, 3};
        case OP_SET_GLOBAL:         return { 0, 2};
        case OP_SET_GLOBAL_16:      return { 0, 3};
        case OP_GET_LOCAL:          return { 1, 2};
        case OP_GET_LOCAL_16:       return { 1, 3};
        case OP_SET_LOCAL:          return { 0, 2};
        case OP_SET_LOCAL_16:       return { 0, 3};
        case OP_SET_UPVALUE:        return { 0, 3};
        case OP_GET_UPVALUE:        return { 1, 3};
        case OP_GET_PROPERTY:       return { 0, 2};
        case OP_GET_PROPERTY_16:    return { 0, 3};
        case OP_SET_PROPERTY:       return {-1, 2};
        case OP_SET_PROPERTY_16:    return {-1, 3};
        case OP_GET_SUPER:          return { 0, 2};
        case OP_GET_SUPER_16:       return { 0, 3};
        case OP_GET_SUBSCRIPT:      return {-1, 1};
        case OP_SET_SUBSCRIPT:      return {-2, 1};

        // compound operator edge-case opcodes.
        case OP_COMPOUND_PROPERTY:      return {-2, 3};
        case OP_COMPOUND_PROPERTY_16:   return {-2, 4};
        case OP_COMPOUND_SUBSCRIPT:     return {-2, 2};

        // unary
        case OP_NEGATE:                 return { 0, 1};
        case OP_NOT:                    return { 0, 1};
        
        // arythmic
        case OP_ADD:                    return {-1, 1};
        case OP_SUBSTRACT:              return {-1, 1};
        case OP_MULTIPLY:               return {-1, 1};
        case OP_DIVIDE:                 return {-1, 1};
        case OP_MODULO:                 return {-1, 1};

        // logical
        case OP_EQUAL:                  return { 0, 1};
        case OP_NOT_EQUAL:              return { 0, 1};
        case OP_GREATER:                return { 0, 1};
        case OP_GREATER_EQUAL:          return { 0, 1};
        case OP_LESS:                   return { 0, 1};
        case OP_LESS_EQUAL:             return { 0, 1};

        // jumps
        case OP_JUMP:                   return {0, 3};
        case OP_JUMP_IF_FALSE:          return {0, 3};
        case OP_JUMP_IF_TRUE:           return {0, 3};
        case OP_LOOP:                   return {0, 3};
        case OP_BREAK:                  return {0, 5};
        case OP_CONTINUE:               return {0, 5};
        
        // calls
        case OP_CALL:                   return { -read_byte(), 2};
        case OP_INVOKE:                 return { -read_byte(), 3};
        case OP_INVOKE_16:              return { -read_byte(), 4};
        case OP_SUPER_INVOKE:           return { -read_byte(), 3};
        case OP_SUPER_INVOKE_16:        return { -read_byte(), 4};

        // special datatypes
        case OP_MAKE_LIST:              return {read_short(), 3};

        // VM constructs
        case OP_CLASS:                  return { 1, 2};
        case OP_CLASS_16:               return { 1, 3};
        case OP_INHERIT:                return {-1, 1};
        case OP_METHOD:                 return {-1, 2};
        case OP_METHOD_16:              return {-1, 3};
        case OP_CLOSE_UPVALUES:         return { 0, 1};
        case OP_POP:                    return {-1, 1};
        case OP_POP_N:                  return {read_byte(), 2};
        case OP_POP_N_16:               return {read_short(), 3};
        case OP_PRINT:                  return {-1, 1};
        case OP_RETURN:                 return {-1, 1};

        case OP_CLOSURE:
        {
            ObjFunction *function = reinterpret_cast<ObjFunction*>(chunk->constant(read_byte()).as.object);
            return { 1, 2 + 3 * function->upvalue_count};
        }
        case OP_CLOSURE_16:
        {
            ObjFunction *function = reinterpret_cast<ObjFunction*>(chunk->constant(read_short()).as.object);
            return { 1, 3 + 3 * function->upvalue_count};
        }
    }

    return {0, 1};
}