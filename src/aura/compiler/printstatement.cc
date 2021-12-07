#include "compiler.ih"

void Compiler::print_statement()
{
    expression();
    consume(TokenType::SEMICOLON, "Expected ';' after value.");
    emit_byte(OP_PRINT);
}