#include "compiler.ih"

void Compiler::subscript([[maybe_unused]] bool can_assign)
{
    expression();
    consume(TokenType::RIGHT_BRACKET, "Expected ']' after subscript parameter.");
    
    if (can_assign && match(TokenType::EQUAL))
    {
        expression();
        emit_byte(OP_SET_SUBSCRIPT);
    }
    else if (can_assign && match_compound_assignment())
    {
        uint8_t opcode = opcode_from_compound();
        expression();
        emit_bytes(OP_COMPOUND_SUBSCRIPT, opcode);
    }
    else
        emit_byte(OP_GET_SUBSCRIPT);

}