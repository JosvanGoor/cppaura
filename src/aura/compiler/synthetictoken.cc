#include "compiler.ih"

Token Compiler::synthetic_token(char const *text)
{
    Token token;
    token.start = text;
    token.length = int(strlen(text));
    return token;
}