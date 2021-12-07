#include "compiler.ih"

void Compiler::var_declaration()
{
    size_t global = parse_variable("Expected variable name.");
    
    if (match(TokenType::EQUAL))
        expression();
    else
        emit_byte(OP_NIL);

    consume(TokenType::SEMICOLON, "Expected ';' after variable declaration");
    define_variable(global);
}