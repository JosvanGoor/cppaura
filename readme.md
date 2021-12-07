# Aura - The toy programming language

## Introduction
Aura is a simple programming language written by Jos van Goor. It is strongly inspired (and partly based on) the lox programming language designed by Robert Nystrom in his book [Crafting Interpreters](http://www.craftinginterpreters.com/).

Internals added: Scaling (call)stack. Stack and callstack now scale up when required.

## Some todo things:
* Exceptions!
* Modules
* Allocate Object should be available in native interface.
* Dicts
* Variable types
* type casts
* Small string optimalisation
* to_string for instances.

## Idea how to do exceptions
When entering a `try` block it pops a "ObjCatchFrame" which contains a `instruction pointer` to the start of the corresponding catch block, a `stack_top pointer` which points to the stack value that should be the stack top after the try block ends, and a `Callframe pointer`, which points to the callframe active when entering the try.

Any value can be thrown (but some value has to be thrown!) and a catch will catch a value in a local (e.g. `catch (foo) { }`). The thrown value will implicitly be wrapped in an `ObjException` which will also contain stack trace information. When a exception is thrown the VM will return runtime to the stored information stored when entering the try, and iterate on any callframes that were active at the time of throwing generating a stack trace. The VM will finally make a call to `discard_orphaned_upvalues`.

An `Orphaned Upvalue` is an upvalue whose lifetime has ended in an unnatural way (by exceptions) These upvalues will be discarded to a certain point at the top of the stack. Note! that upvalues whose scope ends unexpectidly due to `break` or `continue` should still be closed as usual.

## Grammar
This is the outline of the grammar, where additions have been made from lox they are noted below the section.

```
program        -> declaration* EOF ;
```

### Declarations
```
declaration    -> classDecl
                | funDecl
                | varDecl
                | statement ;

classDecl      -> "class" IDENTIFIER ( "<" IDENTIFIER )?
                  "{" function* "}" ;
funDecl        -> "fun" function ;
varDecl        -> "var" IDENTIFIER ( "=" expression )? ";" ;
```

### Statements
```
statement      -> breakStmt
                | continueStmt
                | exprStmt
                | forStmt
                | ifStmt
                | printStmt
                | returnStmt
                | whileStmt
                | block ;

breakStmt      -> "break" ";" ;
continueStmt   -> "continue" ";" ;
exprStmt       -> expression ";" ;
forStmt        -> "for" "(" ( varDecl | exprStmt | ";" )
                            expression? ";"
                            expression? ")" statement ;
ifStmt         -> "if" "(" expression ")" statement ( "else" statement )? ;
printStmt      -> "print" expression ";" ;
returnStmt     -> "return" expression? ";" ;
whileStmt      -> "while" "(" expression ")" statement ;
block          -> "{" declaration* "}" ;
```
* Added break statement
* Added continue statement

### Expressions
```
expression     -> assignment;

assignment     -> ( call "." )? IDENTIFIER "=" assignment
                | ternary;
ternary        -> logic_or "?" expression ":" expression ;
logic_or       -> logic_and ( "or" logic_and )* ;
logic_and      -> equality ( "and" equality )* ;
equality       -> comparison ( ( "!=" | "==" ) comparison )* ;
comparison     -> addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
addition       -> multiplication ( ( "-" | "+" ) multiplication )* ;
multiplication -> unary ( ( "/" | "*" | "%" ) unary )* ;

unary          -> ( "!" | "-" ) unary | call ;
call           -> primary ( "(" arguments? ")" | "." IDENTIFIER )* ;
subscript      -> primary "[" expression "]" ) ;
primary        -> "true" | "false" | "nil" | "this" | list | lambda
                | NUMBER | STRING | IDENTIFIER | "(" expression ")"
                | "super" "." IDENTIFIER ;
list           -> "[" arguments? "]" ;
lambda         -> fun "(" parameters? ")" block ;
```
* Added modulo to multiplication.
* Added ternary statement, associativity and precedence match C++ ternary.
* Added list semantics
* Added subscript semantics.

### Utility rules
```
function       -> IDENTIFIER "(" parameters? ")" block ;
parameters     -> IDENTIFIER ( "," IDENTIFIER )* ;
arguments      -> expression ( "," expression )* ;
```

### Lexical Grammar
```
NUMBER         -> INTEGER | DOUBLE ;
INTEGER        -> DIGIT+ ;
DOUBLE         -> DIGIT+ "." DIGIT+ ;
STRING         -> '"' <any char except '"'>* '"' ;
IDENTIFIER     -> ALPHA ( ALPHA | DIGIT )* ;
ALPHA          -> 'a' ... 'z' | 'A' ... 'Z' | '_' ;
DIGIT          -> '0' ... '9' ;
```
* Added integer & double