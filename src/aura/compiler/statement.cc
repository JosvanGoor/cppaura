#include "compiler.ih"

void Compiler::statement()
{
    if (match(TokenType::PRINT))
        print_statement();
    else if (match(TokenType::BREAK))
        break_statement();
    else if (match(TokenType::CONTINUE))
        continue_statement();
    else if (match(TokenType::FOR))
        for_statement();
    else if (match(TokenType::IF))
        if_statement();
    else if (match(TokenType::RETURN))
        return_statement();
    else if (match(TokenType::WHILE))
        while_statement();
    else if (match(TokenType::LEFT_BRACE))
    {
        begin_scope();
        block();
        end_scope();
    }
    else
        expression_statement();
}