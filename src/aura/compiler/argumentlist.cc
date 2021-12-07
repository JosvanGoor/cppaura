#include "compiler.ih"

uint8_t Compiler::argument_list()
{
    uint8_t arg_count = 0;

    if (!check(TokenType::RIGHT_PAREN))
    {
        do
        {
            if (arg_count == 255)
                error("Cannot have more than 255 arguments.");

            expression();
            ++arg_count;
        }
        while (match(TokenType::COMMA));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments.");
    return arg_count;
}