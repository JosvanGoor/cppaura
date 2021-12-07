#include "compiler.ih"

bool Compiler::check(TokenType type)
{
    return d_current.type == type;
}