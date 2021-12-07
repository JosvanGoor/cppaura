#include "compiler.ih"

void Compiler::named_variable(Token name, bool can_assign)
{
    uint8_t set_op, set_op16;
    uint8_t get_op, get_op16;
    int arg = resolve_local(d_compiler, &name);

    if (arg != -1)
    {
        set_op = OP_SET_LOCAL;
        set_op16 = OP_SET_LOCAL_16;
        get_op = OP_GET_LOCAL;
        get_op16 = OP_GET_LOCAL_16;
    }
    else if ((arg = resolve_upvalue(d_compiler, &name)) != -1)
    {
        set_op = OP_SET_UPVALUE;
        set_op16 = OP_SET_UPVALUE;
        get_op = OP_GET_UPVALUE;
        get_op16 = OP_GET_UPVALUE;
    }
    else
    {
        arg = identifier_constant(&name);
        set_op = OP_SET_GLOBAL;
        set_op16 = OP_SET_GLOBAL_16;
        get_op = OP_GET_GLOBAL;
        get_op16 = OP_GET_GLOBAL_16;
    }

    if (can_assign && match(TokenType::EQUAL)) // normal assignment
    {
        expression();
        emit_var_op(arg, set_op, set_op16);
    }
    else if (can_assign && match_compound_assignment()) // compound assignment
    {
        // get value first
        emit_var_op(arg, get_op, get_op16);

        // store binary op for after expression is pushed.
        uint8_t compound_op = opcode_from_compound();
        expression();
        emit_byte(compound_op);

        // set the value
        emit_var_op(arg, set_op, set_op16);
    }
    else // get
        emit_var_op(arg, get_op, get_op16);
}