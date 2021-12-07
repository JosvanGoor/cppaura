#include "compiler.ih"

void Compiler::return_statement()
{
    if (d_compiler->type == FunctionType::SCRIPT)
        error("Cannot return from top-level code.");

    if (match(TokenType::SEMICOLON))
        emit_return();
    else
    {
        if (d_compiler->type == FunctionType::INITIALIZER)
            error("Cannot return a value from an initializer.");

        expression();
        consume(TokenType::SEMICOLON, "Expect ';' after return value.");
        emit_byte(OP_RETURN);
    }
}