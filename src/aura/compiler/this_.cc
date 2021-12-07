#include "compiler.ih"

void Compiler::this_([[maybe_unused]] bool can_assign)
{
    if (d_classcompiler == nullptr)
    {
        error("Cannot use 'this' outside of a class.");
        return;
    }
    
    variable(false);
}