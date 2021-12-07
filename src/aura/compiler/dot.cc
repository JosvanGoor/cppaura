#include "compiler.ih"

void Compiler::dot(bool can_assign)
{
    consume(TokenType::IDENTIFIER, "Expected property name after '.'.");
    int name = identifier_constant(&d_previous);

    if (name > UINT8_MAX)
    {
        if (can_assign && match(TokenType::EQUAL))
        {
            expression();
            emit_byte(OP_SET_PROPERTY_16);
            emit_short(name);
        }
        else if (can_assign && match_compound_assignment())
        {
            uint8_t compound_op = opcode_from_compound();
            expression();
            emit_byte(OP_COMPOUND_PROPERTY_16);
            emit_short(name);
            emit_byte(compound_op);
        }
        else if (match(TokenType::LEFT_PAREN))
        {
            uint8_t arg_count = argument_list();
            emit_byte(OP_INVOKE_16);
            emit_short(name);
            emit_byte(arg_count);
        }
        else
        {
            emit_byte(OP_GET_PROPERTY_16);
            emit_short(name);
        }
    }
    else
    {
        if (can_assign && match(TokenType::EQUAL))
        {
            expression();
            emit_bytes(OP_SET_PROPERTY, name);
        }
        else if (can_assign && match_compound_assignment())
        {
            uint8_t compound_op = opcode_from_compound();
            expression();
            emit_byte(OP_COMPOUND_PROPERTY);
            emit_bytes(name, compound_op);
        }
        else if (match(TokenType::LEFT_PAREN))
        {
            uint8_t arg_count = argument_list();
            emit_bytes(OP_INVOKE, name);
            emit_byte(arg_count);
        }
        else
            emit_bytes(OP_GET_PROPERTY, name);
    }
}