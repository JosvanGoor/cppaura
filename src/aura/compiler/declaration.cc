#include "compiler.ih"

void Compiler::declaration()
{
    if (match(TokenType::CLASS))
        class_declaration();
    else if (match(TokenType::FUN))
        fun_declaration();
    else if (match(TokenType::VAR))
        var_declaration();
    else
        statement();

    if (d_panic_mode)
        synchronize();
}