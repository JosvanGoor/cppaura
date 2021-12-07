#include "compiler.ih"

void Compiler::parse_precedence(Precedence precedence)
{
    advance();
    ParseFn prefix_rule = get_rule(d_previous.type)->prefix;

    if (prefix_rule == nullptr)
    {
        error("Expected expression.");
        return;
    }

    // update this @ assignment chapter
    bool can_assign = precedence <= Precedence::ASSIGNMENT;
    (this->*prefix_rule)(can_assign);

    // infix part
    while (precedence <= get_rule(d_current.type)->precedence)
    {
        advance();
        ParseFn infix_rule = get_rule(d_previous.type)->infix;
        (this->*infix_rule)(can_assign);
    }

    if (can_assign && match(TokenType::EQUAL))
        error("Invalid assignment target.");
}