#include "compiler.ih"

void Compiler::mark_roots()
{
    LocalCompiler *compiler = d_compiler;

    while (compiler != nullptr)
    {
        d_vm->mark_object(compiler->function);
        compiler = compiler->enclosing;
    }

    // chain call into vm
    d_vm->collect_garbage();
}