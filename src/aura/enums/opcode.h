#ifndef AURA_OPCODE_H
#define AURA_OPCODE_H

#include <cstdint>

namespace aura
{

    enum OpCode : uint8_t
    {
        // constants
        OP_CONSTANT,
        OP_CONSTANT_16,
        OP_ONE, // pushes int value 1
        OP_ZERO, // pushes int value 0
        OP_NIL,
        OP_TRUE,
        OP_FALSE,

        // getting and setting
        OP_DEFINE_GLOBAL,
        OP_DEFINE_GLOBAL_16,
        OP_GET_GLOBAL,
        OP_GET_GLOBAL_16,
        OP_SET_GLOBAL,
        OP_SET_GLOBAL_16,
        OP_GET_LOCAL,
        OP_GET_LOCAL_16,
        OP_SET_LOCAL,
        OP_SET_LOCAL_16,
        OP_SET_UPVALUE, // upvalues index are always 16 bit wide.
        OP_GET_UPVALUE,
        OP_GET_PROPERTY,
        OP_GET_PROPERTY_16,
        OP_SET_PROPERTY,
        OP_SET_PROPERTY_16,
        OP_GET_SUPER,
        OP_GET_SUPER_16,
        OP_GET_SUBSCRIPT,
        OP_SET_SUBSCRIPT,

        // compound operator edge-case opcodes.
        OP_COMPOUND_PROPERTY,       // [ OP_COMPOUND_PROPERTY PROPERTY_NAME BINARY_OP ] <-- opcode layout / operands
        OP_COMPOUND_PROPERTY_16,
        OP_COMPOUND_SUBSCRIPT,      // [ OP_COMPOUND_SUBSCRIPT BINARY_OP ]

        // unary
        OP_NEGATE,
        OP_NOT,
        
        // arythmic
        OP_ADD,
        OP_SUBSTRACT,
        OP_MULTIPLY,
        OP_DIVIDE,
        OP_MODULO,

        // logical
        OP_EQUAL,
        OP_NOT_EQUAL,
        OP_GREATER,
        OP_GREATER_EQUAL,
        OP_LESS,
        OP_LESS_EQUAL,

        // jumps
        OP_JUMP,
        OP_JUMP_IF_FALSE,
        OP_JUMP_IF_TRUE,
        OP_LOOP,
        OP_BREAK, // offset, pops
        OP_CONTINUE, // offset, pops
        
        // calls
        OP_CALL,
        OP_INVOKE,
        OP_INVOKE_16,
        OP_SUPER_INVOKE,
        OP_SUPER_INVOKE_16,

        // special datatypes
        OP_MAKE_LIST,

        // VM constructs
        OP_CLASS,
        OP_CLASS_16,
        OP_INHERIT,
        OP_METHOD,
        OP_METHOD_16,
        OP_CLOSURE,
        OP_CLOSURE_16,
        OP_CLOSE_UPVALUES,
        OP_POP,
        OP_POP_N,
        OP_POP_N_16,
        OP_PRINT,
        OP_RETURN,
    };

}

#endif