#include "compiler.ih"

bool Compiler::match_compound_assignment()
{
    return match(TokenType::PLUS_EQUALS)
        || match(TokenType::MINUS_EQUALS)
        || match(TokenType::STAR_EQUALS)
        || match(TokenType::SLASH_EQUALS)
        || match(TokenType::PERCENT_EQUALS);
}