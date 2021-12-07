#include "compiler.ih"

void Compiler::synchronize()
{
    d_panic_mode = false;

    while (!check(TokenType::EOS))
    {
        if (d_previous.type == TokenType::SEMICOLON)
            return;

        switch (d_current.type)
        {
            case TokenType::CLASS:  [[fallthrough]];
            case TokenType::FUN:    [[fallthrough]];
            case TokenType::VAR:    [[fallthrough]];
            case TokenType::FOR:    [[fallthrough]];
            case TokenType::IF:     [[fallthrough]];
            case TokenType::WHILE:  [[fallthrough]];
            case TokenType::PRINT:  [[fallthrough]];
            case TokenType::RETURN:
                return;

            default: break;
        }

        advance();
    }
}