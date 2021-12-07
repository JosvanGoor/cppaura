#include "virtualmachine.ih"

void VirtualMachine::concatenate()
{
    string buffer = peek(1).to_string() + peek(0).to_string();
    
    char *newchars = reinterpret_cast<char*>(allocate(sizeof(char) * (buffer.size() + 1)));
    memcpy(newchars, buffer.c_str(), buffer.size());
    newchars[buffer.size()] = '\0';

    pop();
    peek(0) = take_string(newchars, buffer.size());
}