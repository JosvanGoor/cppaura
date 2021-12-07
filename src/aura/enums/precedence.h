#ifndef AURA_PRECEDENCE_H
#define AURA_PRECEDENCE_H

namespace aura
{

    enum class Precedence
    {
        NONE,                    
        ASSIGNMENT, // =
        TERNARY,    // ?:
        OR,         // or
        AND,        // and
        EQUALITY,   // == !=
        COMPARISON, // < > <= >=
        TERM,       // + -
        FACTOR,     // * /
        UNARY,      // ! -
        CALL,       // . ()
        PRIMARY
    };

    bool operator<(Precedence lhs, Precedence rhs);

    inline bool operator<(Precedence lhs, Precedence rhs)
    {
        return int(lhs) < int(rhs);
    }

}

#endif