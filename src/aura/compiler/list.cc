#include "compiler.ih"

void Compiler::list([[maybe_unused]] bool can_assign)
{
    int num_entries = parse_list();
    emit_byte(OP_MAKE_LIST);
    emit_short(num_entries);
}