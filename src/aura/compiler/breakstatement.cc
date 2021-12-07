#include "compiler.ih"

void Compiler::break_statement()
{
    if (d_compiler->loops.empty())
    {
        error_at_current("Can't break outside of loop.");
        return;
    }

    consume(TokenType::SEMICOLON, "Expected ';' after break statement.");

    int location = emit_jump(OP_BREAK);
    emit_short(d_compiler->loops.back().num_locals);
    d_compiler->loops.back().breaks.push_back(location);
}