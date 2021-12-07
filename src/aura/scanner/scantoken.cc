#include "scanner.ih"

#include <iostream>

Token Scanner::scan_token()
{
    skip_whitespace();
    d_start = d_current;

    if (is_at_end())
        return make_token(TokenType::EOS);

    char ch = advance();
    
    if (isdigit(ch))
        return scan_number();
    if (isalpha(ch) || ch == '_')
        return scan_identifier();

    switch(ch)
    {
        // single char cases
        case '(': return make_token(TokenType::LEFT_PAREN);
        case ')': return make_token(TokenType::RIGHT_PAREN);
        case '{': return make_token(TokenType::LEFT_BRACE);
        case '}': return make_token(TokenType::RIGHT_BRACE);
        case '[': return make_token(TokenType::LEFT_BRACKET);
        case ']': return make_token(TokenType::RIGHT_BRACKET);
        case ':': return make_token(TokenType::COLON);
        case ',': return make_token(TokenType::COMMA);
        case '.': return make_token(TokenType::DOT);
        case '?': return make_token(TokenType::QUESTIONMARK);
        case ';': return make_token(TokenType::SEMICOLON);

        // dubble char
        case '!': return make_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        case '=': return make_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        case '<': return make_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        case '>': return make_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);    
        case '+': return make_token(match('=') ? TokenType::PLUS_EQUALS : TokenType::PLUS);         // TODO: ++
        case '-': return make_token(match('=') ? TokenType::MINUS_EQUALS : TokenType::MINUS);       // TODO: --, parse -- as two minusses in unary or smh
        case '*': return make_token(match('=') ? TokenType::STAR_EQUALS : TokenType::STAR);
        case '/': return make_token(match('=') ? TokenType::SLASH_EQUALS : TokenType::SLASH);
        case '%': return make_token(match('=') ? TokenType::PERCENT_EQUALS : TokenType::PERCENT);   // TODO: add %=

        // literal
        case '"': return scan_string();
    }

    return error_token("Unexpected character");
}