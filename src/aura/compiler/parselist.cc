#include "compiler.ih"

int Compiler::parse_list()
{
    int num_entries = 0;

    if (!check(TokenType::RIGHT_BRACKET))
    {
        do
        {
            if (num_entries == UINT16_MAX)
                error("Cannot initialize list with more than 65535 entries.");

            expression();
            ++num_entries;
        }
        while (match(TokenType::COMMA));
    }

    consume(TokenType::RIGHT_BRACKET, "Expected ']' after list.");
    return num_entries;
}