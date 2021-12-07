#include "virtualmachine.ih"

void VirtualMachine::repl()
{
    std::string line;

    while (true)
    {
        cout << "> ";

        if (!getline(cin, line))
        {
            cout << "\n";
            break;
        }

        char *chars = new char[line.size() + 1];
        copy(line.c_str(), line.c_str() + line.size(), chars);
        chars[line.size()] = '\0';
        
        interpret(chars);
    }
}