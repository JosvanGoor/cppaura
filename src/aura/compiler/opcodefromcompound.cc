#include "compiler.ih"

uint8_t Compiler::opcode_from_compound()
{
    switch (d_previous.type)
    {
        case TokenType::PLUS_EQUALS: return OP_ADD;
        case TokenType::MINUS_EQUALS: return OP_SUBSTRACT;
        case TokenType::STAR_EQUALS: return OP_MULTIPLY;
        case TokenType::SLASH_EQUALS: return OP_DIVIDE;
        case TokenType::PERCENT_EQUALS: return OP_MODULO;
        default:
            error("opcode_from_compound called for wrong token.");
    }
    return OP_RETURN;
}