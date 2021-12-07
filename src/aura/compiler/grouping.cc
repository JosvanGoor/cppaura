#include "compiler.ih"

void Compiler::grouping([[maybe_unused]] bool can_assign)
{
    expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
}