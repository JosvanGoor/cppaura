#include "compiler.ih"

ObjFunction *Compiler::compile(char const *source)
{
    d_scanner = Scanner{source};

    LocalCompiler compiler;
    init_compiler(&compiler, FunctionType::SCRIPT);

    advance();
    while (!match(TokenType::EOS))
        declaration();

    ObjFunction *function = end_compiler();
    return d_had_error ? nullptr : function;
}