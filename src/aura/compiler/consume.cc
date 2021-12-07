#include "compiler.ih"

void Compiler::consume(TokenType type, char const *on_error)
{
    if (d_current.type == type)
    {
        advance();
        return;
    }

    error_at_current(on_error);
}
