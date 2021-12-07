#include "compiler.ih"

void Compiler::expression()
{
    parse_precedence(Precedence::ASSIGNMENT);
}