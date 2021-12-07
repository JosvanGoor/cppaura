#include "compiler.ih"

void Compiler::unary([[maybe_unused]] bool can_assign)
{
    TokenType oper = d_previous.type;
    parse_precedence(Precedence::UNARY);

    switch(oper)
    {
        case TokenType::BANG:
            emit_byte(OP_NOT);
            break;
            
        case TokenType::MINUS:
            emit_byte(OP_NEGATE);
            break;
        
        default:
            return;
    }
}