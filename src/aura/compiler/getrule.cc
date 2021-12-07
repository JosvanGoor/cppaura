#include "compiler.ih"

Compiler::ParseRule *Compiler::get_rule(TokenType type)
{
    return &parse_rules[int(type)];
}