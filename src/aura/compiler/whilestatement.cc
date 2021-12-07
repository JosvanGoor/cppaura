#include "compiler.ih"

void Compiler::while_statement()
{
    int loop_start = current_chunk()->code_length();
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'while'.");
    expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after condition.");

    // condition false -> exit loop.
    int exit_jump = emit_jump(OP_JUMP_IF_FALSE);

    emit_byte(OP_POP); // pop exit_jump true
    begin_loop(loop_start);
    statement(); // while body
    
    emit_loop(OP_LOOP, loop_start); // back to condition.
    patch_jump(exit_jump);
    emit_byte(OP_POP); // pop exit_jump false
    end_loop();
}