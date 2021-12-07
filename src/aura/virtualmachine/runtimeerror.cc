#include "virtualmachine.ih"

void VirtualMachine::runtime_error(char const *message)
{
    if (message && message[0] != '\0')
        cerr << message << "\n";
    
    for (size_t idx = d_frame_count; idx--; )
    {
        ObjFunction *function = d_frames[idx].function;

        size_t instruction = d_frames[idx].ip - function->chunk.code() - 1;
        cerr << "    [line " << function->chunk.instruction_line(instruction) << "] in ";
        if (function->name == nullptr)
            cerr << "script\n";
        else
            cerr << aura::to_string(function->name) << "()\n";
    }

    reset_stack();
}