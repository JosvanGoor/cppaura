#include "compiler.ih"

void Compiler::for_statement()
{
    begin_scope();
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'for'.");
    
    // initializer clause
    if (match(TokenType::SEMICOLON))
    {
        // no semicolon
    } else if (match(TokenType::VAR))
        var_declaration();
    else
        expression_statement();

    // conditional clause
    int loop_start = current_chunk()->code_length();
    int exit_jump = -1;
    if (!match(TokenType::SEMICOLON))
    {
        expression();
        consume(TokenType::SEMICOLON, "Expected ';' after condition clause.");

        // if false we exit the jump.
        exit_jump = emit_jump(OP_JUMP_IF_FALSE);
        emit_byte(OP_POP); // pop condition
    }

    // update clause, this is a weird one since it is executed last.
    if (!match(TokenType::RIGHT_PAREN))
    {
        int body_jump = emit_jump(OP_JUMP);
        int increment_start = current_chunk()->code_length();
        expression();
        emit_byte(OP_POP);
        consume(TokenType::RIGHT_PAREN, "Expected ')' after for clauses.");

        emit_loop(OP_LOOP, loop_start); // jump to conditional after increment
        loop_start = increment_start; // end of loop jumps to increment
        patch_jump(body_jump); // jumps over update to body
    }

    // body
    begin_loop(loop_start);
    statement();
    emit_loop(OP_LOOP, loop_start);

    if (exit_jump != -1)
    {
        patch_jump(exit_jump);
        emit_byte(OP_POP); // conditional clause condition
    }

    end_loop();
    end_scope();
}