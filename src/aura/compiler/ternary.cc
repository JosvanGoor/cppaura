#include "compiler.ih"

void Compiler::ternary([[maybe_unused]] bool can_assign)
{
    // conditional has been parsed & '?'
    int false_side = emit_jump(OP_JUMP_IF_FALSE);
    emit_byte(OP_POP); // pop conditional, true case
    
    expression();
    int exit = emit_jump(OP_JUMP);

    consume(TokenType::COLON, "Expected ':' between expressions.");
    patch_jump(false_side);
    emit_byte(OP_POP); // pop conditional, false case
    
    expression();
    patch_jump(exit);
}