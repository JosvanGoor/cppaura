#include "compiler.ih"

int Compiler::parse_variable(char const *error_message)
{
    consume(TokenType::IDENTIFIER, error_message);

    declare_variable();
    if (d_compiler->scope_depth > 0)
        return 0; // its local

    return identifier_constant(&d_previous);
}