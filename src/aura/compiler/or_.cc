#include "compiler.ih"

void Compiler::or_([[maybe_unused]] bool can_assign)
{
    int exit_jump = emit_jump(OP_JUMP_IF_TRUE);
    emit_byte(OP_POP); // pop the false value
    
    parse_precedence(Precedence::OR);
    patch_jump(exit_jump);
    // leave the final truth value
}