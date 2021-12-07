#include <fstream>
#include <iostream>


#include "aura/chunk/chunk.h"
#include "aura/debug/debug.h"
#include "aura/enums/opcode.h"

using namespace std;
using namespace aura;

int main(int argc, char *argv[])
{
    VirtualMachine vm;
    
    if (argc == 1)
        vm.repl();
    else if (argc == 2)
        vm.run_file(argv[1]);
    else
    {
        cout << "Usage: aura [path]\n";
        return -3;
    }
}