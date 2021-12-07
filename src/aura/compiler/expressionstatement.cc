#include "compiler.ih"

void Compiler::expression_statement()
{
    expression();
    consume(TokenType::SEMICOLON, "Expected ';' after expression");
    emit_byte(OP_POP);
}