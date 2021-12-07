#include "compiler.ih"

void Compiler::floating([[maybe_unused]] bool can_assign)
{
    double value = stod(string{d_previous.start, d_previous.start + d_previous.length});
    emit_constant(value);
}