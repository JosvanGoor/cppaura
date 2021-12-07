#include "compiler.ih"

void Compiler::fun_declaration()
{
    int global = parse_variable("Expected function name");
    mark_initialized();

    function(FunctionType::FUNCTION);
    define_variable(global);
}