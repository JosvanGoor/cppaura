#ifndef AURA_SCANNER_H
#define AURA_SCANNER_H

#include <string>
#include "../enums/tokentype.h"

namespace aura
{

    struct Token
    {
        TokenType type = TokenType::ERROR;
        char const *start = "";
        size_t length = 0;
        size_t line = 0;
    };

    class Scanner
    {
        char const *d_source;

        size_t d_line;
        char const *d_start; // parsing iterators
        char const *d_current;

        public:
            Scanner(); // empty init
            Scanner(char const *source);
            ~Scanner();

            Scanner &operator=(Scanner &&other);

            Token scan_token();

        private:
            bool is_at_end();
            void skip_whitespace();
            TokenType identifier_type();

            char peek();
            char advance();
            char peek_next();
            bool match(char ch);

            Token scan_identifier();
            Token scan_number();
            Token scan_string();
            

            Token make_token(TokenType type);
            Token error_token(char const *message);

            // block copies
            Scanner(Scanner const &) = delete;
            Scanner &operator=(Scanner const &) = delete;
    };

}

#endif