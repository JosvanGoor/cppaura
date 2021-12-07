#include "compiler.ih"

void Compiler::function(FunctionType type)
{
    LocalCompiler compiler;
    init_compiler(&compiler, type);
    begin_scope();

    consume(TokenType::LEFT_PAREN, "Expected '(' after function name.");

    if (!check(TokenType::RIGHT_PAREN))
    {
        do
        {
            ++d_compiler->function->arity;
            if (d_compiler->function->arity > 255)
                error_at_current("Cannot have more than 255 parameters.");

            uint8_t param_constant = parse_variable("Expected variable name.");
            define_variable(param_constant);
        }
        while (match(TokenType::COMMA));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters");

    // body
    consume(TokenType::LEFT_BRACE, "Expected '{' before function body.");
    block();

    ObjFunction *function = end_compiler();
    size_t index = make_constant(function);
    
    if (index > UINT8_MAX)
    {
        emit_byte(OP_CLOSURE_16);
        emit_short(index);
    }
    else
        emit_bytes(OP_CLOSURE, index);

    for (int idx = 0; idx < function->upvalue_count; ++idx)
    {
        emit_byte(compiler.upvalues[idx].is_local ? 1 : 0);
        emit_short(compiler.upvalues[idx].index);
    }
}