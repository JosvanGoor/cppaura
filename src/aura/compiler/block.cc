#include "compiler.ih"

void Compiler::block()
{
    while (!check(TokenType::RIGHT_BRACE) && !check(TokenType::EOS))
        declaration();

    consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
}