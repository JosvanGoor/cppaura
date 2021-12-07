#include "compiler.ih"

void Compiler::method()
{
    consume(TokenType::IDENTIFIER, "Expected method name.");
    int constant = identifier_constant(&d_previous);
    
    FunctionType type = FunctionType::METHOD;
    
    if (d_previous.length == d_classcompiler->name.length
        && memcmp(d_previous.start, d_classcompiler->name.start, d_previous.length) == 0)
    {
        type = FunctionType::INITIALIZER;
    }

    function(type);
    
    if (constant > UINT8_MAX)
    {
        emit_byte(OP_METHOD_16);
        emit_short(constant);
    }
    else
        emit_bytes(OP_METHOD, constant);

}