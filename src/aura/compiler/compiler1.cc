#include "compiler.ih"

Compiler::Compiler(VirtualMachine *vm)
:   d_compiler(nullptr),
    d_classcompiler(nullptr),
    d_vm(vm),
    d_scanner(),
    d_current(),
    d_previous(),
    d_had_error(false),
    d_panic_mode(false)
{ }