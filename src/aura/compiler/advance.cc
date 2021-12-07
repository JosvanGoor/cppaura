#include "compiler.ih"

void Compiler::advance()
{
    d_previous = d_current;

    while (true)
    {
        d_current = d_scanner.scan_token();
        if (d_current.type != TokenType::ERROR)
            break;

        error_at_current(d_current.start);
    }
}