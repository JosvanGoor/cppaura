#include "compiler.ih"

void Compiler::binary([[maybe_unused]] bool can_assign)
{
    TokenType oper = d_previous.type;

    ParseRule *rule = get_rule(oper);
    parse_precedence(Precedence(int(rule->precedence) + 1));

    switch (oper)
    {
        case TokenType::EQUAL_EQUAL:    emit_byte(OP_EQUAL); break;
        case TokenType::BANG_EQUAL:     emit_byte(OP_NOT_EQUAL); break;
        case TokenType::GREATER:        emit_byte(OP_GREATER); break;
        case TokenType::GREATER_EQUAL:  emit_byte(OP_GREATER_EQUAL); break;
        case TokenType::LESS:           emit_byte(OP_LESS); break;
        case TokenType::LESS_EQUAL:     emit_byte(OP_LESS_EQUAL); break;

        case TokenType::PLUS:           emit_byte(OP_ADD); break;
        case TokenType::MINUS:          emit_byte(OP_SUBSTRACT); break;
        case TokenType::STAR:           emit_byte(OP_MULTIPLY); break;
        case TokenType::SLASH:          emit_byte(OP_DIVIDE); break;
        case TokenType::PERCENT:        emit_byte(OP_MODULO); break;

        default: break;
            // doesnt happen
    }
}