#include "compiler.ih"

void Compiler::if_statement()
{
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
    expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after condition.");

    int then_jump = emit_jump(OP_JUMP_IF_FALSE);
    emit_byte(OP_POP); // pop then_jump truthy value

    statement();
    int else_jump = emit_jump(OP_JUMP);
    patch_jump(then_jump);
    emit_byte(OP_POP); // pop then_jump falsey

    if (match(TokenType::ELSE))
        statement();
    patch_jump(else_jump);
}