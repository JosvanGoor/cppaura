#include "compiler.ih"

bool Compiler::match(TokenType type)
{
    if (!check(type))
        return false;
    
    advance();
    return true;
}