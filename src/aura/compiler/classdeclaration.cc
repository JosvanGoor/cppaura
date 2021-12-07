#include "compiler.ih"

void Compiler::class_declaration()
{
    consume(TokenType::IDENTIFIER, "Expected class name.");
    Token classname = d_previous;

    int name_constant = identifier_constant(&d_previous);
    declare_variable();

    if (name_constant > UINT8_MAX)
    {
        emit_byte(OP_CLASS_16);
        emit_short(name_constant);
    }
    else
        emit_bytes(OP_CLASS, name_constant);
    define_variable(name_constant);

    ClassCompiler class_compiler = 
    {
        d_previous,
        d_classcompiler
    };
    d_classcompiler = &class_compiler;

    if (match(TokenType::ISA)) // inheritance
    {
        consume(TokenType::IDENTIFIER, "Expected superclass name.");
        variable(false);

        if (identifiers_equal(&classname, &d_previous))
            error("A class cannot inherit from itself.");
        
        // bind super
        begin_scope();
        add_local(synthetic_token("super"));
        define_variable(0);

        named_variable(classname, false);
        emit_byte(OP_INHERIT);
        class_compiler.has_superclass = true;
    }

    named_variable(classname, false);
    consume(TokenType::LEFT_BRACE, "Expected '{' before class body.");
    while (!check(TokenType::RIGHT_BRACE) && !check(TokenType::EOS))
        method();
    consume(TokenType::RIGHT_BRACE, "Expected '}' after class body.");
    emit_byte(OP_POP);

    if (d_classcompiler->has_superclass)
        end_scope();

    d_classcompiler = class_compiler.enclosing;
}