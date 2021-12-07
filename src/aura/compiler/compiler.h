#ifndef AURA_COMPILER_H
#define AURA_COMPILER_H

#include <string>
#include <vector>

#include "../enums/functiontype.h"
#include "../enums/precedence.h"
#include "../value/value.h"
#include "../scanner/scanner.h"
#include "../objects/objfunction/objfunction.h"

namespace aura
{

    // forward decl
    class Chunk;
    class VirtualMachine;

    class Compiler
    {
        using ParseFn = void (Compiler::*)(bool);
        // Internal data structures (POD types)
        struct Loop;
        struct Local;
        struct Upvalue;
        struct ParseRule;
        struct ClassCompiler;
        struct LocalCompiler;

        LocalCompiler *d_compiler;  // non owning
        ClassCompiler *d_classcompiler; // non owning
        VirtualMachine *d_vm;       // non owning

        Scanner d_scanner;
        static ParseRule parse_rules[];

        // parser stuff
        Token d_current;
        Token d_previous;
        bool d_had_error;
        bool d_panic_mode; 

        public:
            Compiler(VirtualMachine *vm);
            
            // compile time gcc
            void mark_roots();

            ObjFunction *compile(char const *source);

        private:
            Compiler(Compiler const &) = delete;
            Compiler &operator=(Compiler const &) = delete;

            // util
            void advance();
            bool check(TokenType type);
            bool match(TokenType type);
            void consume(TokenType type, char const *on_error);
            bool identifiers_equal(Token *lhs, Token *rhs);
            
            // stack effect calculation
            int chunk_max_stacksize(Chunk *chunk);
            std::pair<int, size_t> opcode_stack_effect(Chunk *chunk, size_t offset);

            bool match_compound_assignment();
            uint8_t opcode_from_compound();

            void emit_pop(uint32_t pops);
            void emit_byte(uint8_t byte);
            void emit_bytes(uint8_t byte1, uint8_t byte2);
            void emit_short(uint16_t bytes);
            void emit_constant(Value value);
            void emit_var_op(int arg, uint8_t op, uint8_t op16);
            void emit_return();

            ObjFunction *end_compiler();
            void init_compiler(LocalCompiler *compiler, FunctionType type);
            Chunk *current_chunk();
            ParseRule *get_rule(TokenType type);
            size_t make_constant(Value value);
            Token synthetic_token(char const *text);

            // special types helpers
            int parse_list();

            // error reporting
            void error(char const *message); // at previous
            void error_at(Token const &token, char const *message);
            void error_at_current(char const *message);
            void synchronize();

            // scope /frame stuff
            void begin_scope();
            void end_scope();
            void begin_loop(int start_pos);
            void end_loop();

            // jump stuff
            int emit_jump(uint8_t instruction);
            void patch_jump(int offset);
            void emit_loop(uint8_t instruction, int loop_start);

            // variable helpers
            void add_local(Token name);
            void mark_initialized();
            void declare_variable();
            void define_variable(size_t index);
            void named_variable(Token name, bool can_assign);
            int parse_variable(char const *error_message);
            int identifier_constant(Token *name);
            int resolve_local(LocalCompiler *compiler, Token *name);
            int resolve_upvalue(LocalCompiler *compiler, Token *name);
            int add_upvalue(LocalCompiler *compiler, uint16_t index, bool is_local);

            // function helpers
            void method();
            void function(FunctionType type);
            uint8_t argument_list();

            // declarations
            void declaration();
            void class_declaration();
            void fun_declaration();
            void var_declaration();

            // statements
            void statement();
            void block();
            void break_statement();
            void continue_statement();
            void expression_statement();
            void for_statement();
            void if_statement();
            void print_statement();
            void return_statement();
            void while_statement();

            // expressions
            void expression();
            void and_(bool can_assign);
            void binary(bool can_assign);
            void call(bool can_assign);
            void continue_(bool can_assign);
            void dot(bool can_assign);
            void floating(bool can_assign);
            void grouping(bool can_assign);
            void integer(bool can_assign);
            void lambda(bool can_assign);
            void list(bool can_assign);
            void literal(bool can_assign);
            void or_(bool can_assign);
            void string_(bool can_assign);
            void subscript(bool can_assign);
            void super_(bool can_assign);
            void ternary(bool can_assign);
            void this_(bool can_assign);
            void unary(bool can_assign);
            void variable(bool can_assign);

            void parse_precedence(Precedence precedence);
    };

    struct Compiler::Loop
    {
        int loop_start = 0;
        uint16_t num_locals = 0;
        std::vector<size_t> breaks; // 2patch breaks.
    };

    struct Compiler::Local
    {
        Token name;
        int depth = 0;
        bool is_captured = false;
    };

    struct Compiler::Upvalue
    {
        uint16_t index = 0;
        bool is_local = false;
    };

    struct Compiler::ParseRule
    {
        ParseFn prefix;
        ParseFn infix;
        Precedence precedence;
    };

    struct Compiler::ClassCompiler
    {
        Token name;
        bool has_superclass = false;
        ClassCompiler *enclosing = nullptr;
    };

    struct Compiler::LocalCompiler
    {
        LocalCompiler *enclosing;

        FunctionType type = FunctionType::SCRIPT;
        ObjFunction *function = nullptr;

        int scope_depth = 0;
        std::vector<Loop> loops;
        std::vector<Local> locals;
        std::vector<Upvalue> upvalues;
    };

}

#endif