#include "virtualmachine.ih"

void VirtualMachine::run_file(char const *file)
{
    char *source = read_file(file);
    InterpretResult result = interpret(source);

    if (result == InterpretResult::COMPILE_ERROR)
        exit(-100);
    if (result == InterpretResult::RUNTIME_ERROR)
        exit(-105);
}