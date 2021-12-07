#include "compiler.ih"

void Compiler::continue_statement()
{
    if (d_compiler->loops.empty())
    {
        error_at_current("Can't continue outside of a loop.");
        return;
    }

    consume(TokenType::SEMICOLON, "Expected ';' after continue statement.");

    emit_loop(OP_CONTINUE, d_compiler->loops.back().loop_start);
    emit_short(d_compiler->loops.back().num_locals);
}