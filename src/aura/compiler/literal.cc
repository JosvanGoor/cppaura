#include "compiler.ih"

void Compiler::literal([[maybe_unused]] bool can_assign)
{
    switch (d_previous.type)
    {
        case TokenType::FALSE:  emit_byte(OP_FALSE); break;
        case TokenType::NIL:    emit_byte(OP_NIL); break;
        case TokenType::TRUE:   emit_byte(OP_TRUE); break;

        default: break;
            // unreachable;
    }
}