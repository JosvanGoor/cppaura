#include "debug.ih"

size_t aura::disassemble_instruction(Chunk const &chunk, size_t offset)
{
    cout << setw(4) << right << setfill('0') << offset << " ";
    if (offset > 0 && chunk.consecutive_line(offset))
        cout << "   | ";
    else
        cout << setw(4) << setfill(' ') << chunk.instruction_line(offset) << " ";

    uint8_t instruction = chunk.code()[offset];
    switch(instruction)
    {
        case OP_CONSTANT:               return constant_instruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_16:            return constant16_instruction("OP_CONSTANT_16", chunk, offset);
        case OP_ONE:                    return simple_instruction("OP_ONE", offset);
        case OP_ZERO:                   return simple_instruction("OP_ZERO", offset);
        case OP_NIL:                    return simple_instruction("OP_NIL", offset);
        case OP_FALSE:                  return simple_instruction("OP_FALSE", offset);
        case OP_TRUE:                   return simple_instruction("OP_TRUE", offset);

        case OP_DEFINE_GLOBAL:          return constant_instruction("OP_DEFINE_GLOBAL", chunk, offset);
        case OP_DEFINE_GLOBAL_16:       return constant16_instruction("OP_DEFINE_GLOBAL_16", chunk, offset);
        case OP_GET_GLOBAL:             return constant_instruction("OP_GET_GLOBAL", chunk, offset);
        case OP_GET_GLOBAL_16:          return constant16_instruction("OP_GET_GLOBAL_16", chunk, offset);
        case OP_SET_GLOBAL:             return constant_instruction("OP_SET_GLOBAL", chunk, offset);
        case OP_SET_GLOBAL_16:          return constant16_instruction("OP_SET_GLOBAL_16", chunk, offset);
        case OP_GET_LOCAL:              return byte_instruction("OP_GET_LOCAL", chunk, offset, false);
        case OP_GET_LOCAL_16:           return byte16_instruction("OP_GET_LOCAL_16", chunk, offset);
        case OP_SET_LOCAL:              return byte_instruction("OP_SET_LOCAL", chunk, offset, false);
        case OP_SET_LOCAL_16:           return byte16_instruction("OP_SET_LOCAL_16", chunk, offset);
        case OP_GET_UPVALUE:            return byte16_instruction("OP_GET_UPVALUE", chunk, offset);
        case OP_SET_UPVALUE:            return byte16_instruction("OP_SET_UPVALUE", chunk, offset);
        case OP_GET_PROPERTY:           return constant_instruction("OP_GET_PROPERTY", chunk, offset);
        case OP_GET_PROPERTY_16:        return constant16_instruction("OP_GET_PROPERTY_16", chunk, offset);
        case OP_SET_PROPERTY:           return constant_instruction("OP_SET_PROPERTY", chunk, offset);
        case OP_SET_PROPERTY_16:        return constant16_instruction("OP_SET_PROPERTY_16", chunk, offset);
        case OP_GET_SUPER:              return constant_instruction("OP_GET_SUPER", chunk, offset);
        case OP_GET_SUPER_16:           return constant16_instruction("OP_GET_SUPER_16", chunk, offset);
        case OP_GET_SUBSCRIPT:          return simple_instruction("OP_GET_SUBSCRIPT", offset);
        case OP_SET_SUBSCRIPT:          return simple_instruction("OP_SET_SUBSCRIPT", offset);

        case OP_COMPOUND_PROPERTY:      return compound_instruction("OP_COMPOUND_PROPERTY", chunk, offset);
        case OP_COMPOUND_PROPERTY_16:   return compound16_instruction("OP_COMPOUND_PROPERTY_16", chunk, offset);
        case OP_COMPOUND_SUBSCRIPT:     return byte_instruction("OP_COMPOUND_SUBSCRIPT", chunk, offset, true);

        case OP_NEGATE:                 return simple_instruction("OP_NEGATE", offset);
        case OP_NOT:                    return simple_instruction("OP_NOT", offset);

        case OP_ADD:                    return simple_instruction("OP_ADD", offset);
        case OP_SUBSTRACT:              return simple_instruction("OP_SUBSTRACT", offset);
        case OP_MULTIPLY:               return simple_instruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:                 return simple_instruction("OP_DIVIDE", offset);
        case OP_MODULO:                 return simple_instruction("OP_MODULO", offset);

        case OP_EQUAL:                  return simple_instruction("OP_EQUAL", offset);
        case OP_NOT_EQUAL:              return simple_instruction("OP_NOT_EQUAL", offset);
        case OP_GREATER:                return simple_instruction("OP_GREATER", offset);
        case OP_GREATER_EQUAL:          return simple_instruction("OP_GREATER_EQUAL", offset);
        case OP_LESS:                   return simple_instruction("OP_LESS", offset);
        case OP_LESS_EQUAL:             return simple_instruction("OP_LESS_EQUAL", offset);

        case OP_JUMP:                   return jump_instruction("OP_JUMP", 1, chunk, offset);
        case OP_JUMP_IF_FALSE:          return jump_instruction("OP_JUMP_IF_FALSE", 1, chunk, offset);
        case OP_JUMP_IF_TRUE:           return jump_instruction("OP_JUMP_IF_TRUE", 1, chunk, offset);
        case OP_LOOP:                   return jump_instruction("OP_LOOP", -1, chunk, offset);
        case OP_BREAK:                  return loop_instruction("OP_BREAK", 1, chunk, offset);
        case OP_CONTINUE:               return loop_instruction("OP_CONTINUE", -1, chunk, offset);
        
        case OP_CALL:                   return byte_instruction("OP_CALL", chunk, offset, false);
        case OP_INVOKE:                 return invoke_instruction("OP_INVOKE", chunk, offset);
        case OP_INVOKE_16:              return invoke16_instruction("OP_INVOKE_16", chunk, offset);
        case OP_SUPER_INVOKE:           return invoke_instruction("OP_SUPER_INVOKE", chunk, offset);
        case OP_SUPER_INVOKE_16:        return invoke16_instruction("OP_SUPER_INVOKE_16", chunk, offset);

        case OP_MAKE_LIST:              return list_instruction("OP_MAKE_LIST", chunk, offset);

        case OP_CLASS:                  return constant_instruction("OP_CLASS", chunk, offset);
        case OP_CLASS_16:               return constant16_instruction("OP_CLASS_16", chunk, offset);
        case OP_INHERIT:                return simple_instruction("OP_INHERIT", offset);
        case OP_METHOD:                 return constant_instruction("OP_METHOD", chunk, offset);
        case OP_METHOD_16:              return constant16_instruction("OP_METHOD_16", chunk, offset);
        case OP_CLOSE_UPVALUES:         return simple_instruction("OP_CLOSE_UPVALUES", offset);
        case OP_POP:                    return simple_instruction("OP_POP", offset);
        case OP_POP_N:                  return byte_instruction("OP_POP_N", chunk, offset, false);
        case OP_POP_N_16:               return byte16_instruction("OP_POP_N_16", chunk, offset);
        case OP_PRINT:                  return simple_instruction("OP_PRINT", offset);
        case OP_RETURN:                 return simple_instruction("OP_RETURN", offset);

        case OP_CLOSURE: // bit of a special carrot
        {
            ++offset;
            uint16_t constant = chunk.code()[offset++];
            cout << setw(24) << setfill(' ') << left << "OP_CLOSURE" << " " << setw(4) << constant;
            cout << chunk.constant(constant) << "\n";
            
            ObjFunction *function = reinterpret_cast<ObjFunction*>(chunk.constant(constant).as.object);
            for (int idx = 0; idx < function->upvalue_count; ++idx)
            {
                int is_local = chunk.code()[offset++];
                uint16_t index = chunk.code()[offset++] << 8;
                index |= chunk.code()[offset++];

                cout << setw(4) << right << setfill('0') << (offset - 2) << left << "      |                     ";
                cout << setfill(' ') << setw(8) << (is_local == 1 ? "local" : "upvalue") << index << "\n";
            }

            return offset;
        }
        case OP_CLOSURE_16: // bit of a special carrot
        {
            ++offset;
            uint16_t constant = chunk.code()[offset++] << 8;
            constant |= chunk.code()[offset++];
            cout << setw(24) << setfill(' ') << left << "OP_CLOSURE" << " " << setw(4) << constant;
            cout << chunk.constant(constant) << "\n";
            
            ObjFunction *function = reinterpret_cast<ObjFunction*>(chunk.constant(constant).as.object);
            for (int idx = 0; idx < function->upvalue_count; ++idx)
            {
                int is_local = chunk.code()[offset++];
                uint16_t index = chunk.code()[offset++] << 8;
                index |= chunk.code()[offset++];

                cout << setw(4) << (offset - 2) << "      |                     ";
                cout << setfill(' ') << setw(8) << (is_local == 1 ? "local" : "upvalue") << index << "\n";
            }

            return offset;
        }

        default:
            cout << "unknown...\n";
            return offset + 1; // SHOULD NOT BE REACHABLE
    }
}