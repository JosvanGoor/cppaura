#include "compiler.ih"

void Compiler::super_([[maybe_unused]] bool can_assign)
{
    if (d_classcompiler == nullptr)
        error("Cannot use 'super' outside of a class.");
    else if (!d_classcompiler->has_superclass)
        error("Cannot use 'super' in a class with no superclass.");

    consume(TokenType::DOT, "Expected '.' after 'super'.");
    consume(TokenType::IDENTIFIER, "Expected superclass method name.");
    int name = identifier_constant(&d_previous);

    named_variable(synthetic_token("this"), false);
    
    if (match(TokenType::LEFT_PAREN)) // super_invoke
    {
        uint8_t arg_count = argument_list();
        named_variable(synthetic_token("super"), false);

        if (name > UINT8_MAX)
        {
            emit_byte(OP_SUPER_INVOKE_16);
            emit_short(name);
            emit_byte(arg_count);
        }
        else
        {
            emit_bytes(OP_SUPER_INVOKE, name);
            emit_byte(arg_count);
        }
    }
    else
    {
        named_variable(synthetic_token("super"), false);

        if (name > UINT8_MAX)
        {
            emit_byte(OP_GET_SUPER_16);
            emit_short(name);
        }
        else
            emit_bytes(OP_GET_SUPER, name);
    }
}