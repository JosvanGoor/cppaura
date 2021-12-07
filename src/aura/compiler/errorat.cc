#include "compiler.ih"

void Compiler::error_at(Token const &token, char const *message)
{
    if (d_panic_mode)
        return;
    d_panic_mode = true;

    cerr << "[line " << token.line << "] Error";

    if (token.type == TokenType::EOS)
        cerr << " at end";
    else if (token.type == TokenType::ERROR)
    { /* Nozink */ }
    else
        cerr << " at '" << string_view(token.start, token.length) << "'";

    cerr << ": " << message << "\n";
    d_had_error = true;
}