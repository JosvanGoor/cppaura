#include "compiler.ih"

void Compiler::and_([[maybe_unused]] bool can_assign)
{
    int end_jump = emit_jump(OP_JUMP_IF_FALSE);
    emit_byte(OP_POP); // end_jump truthy

    parse_precedence(Precedence::AND);
    patch_jump(end_jump);
    // dont pop it we want to keep a value of the right
    // truthy-ness on the stack.
}