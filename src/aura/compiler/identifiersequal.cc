#include "compiler.ih"

bool Compiler::identifiers_equal(Token *lhs, Token *rhs)
{
    if (lhs->length != rhs->length)
        return false;

    return memcmp(lhs->start, rhs->start, lhs->length) == 0;
}
