#include "compiler.ih"

void Compiler::lambda([[maybe_unused]] bool can_assign)
{
    function(FunctionType::LAMBDA);
}