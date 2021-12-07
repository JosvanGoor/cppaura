#ifndef AURA_VALUE_H
#define AURA_VALUE_H

#include <string>
#include <iostream>

#include "../enums/objecttype.h"
#include "../enums/valuetype.h"

namespace aura
{
    
    class Object;

    struct Value
    {
        ValueType type;
        union
        {
            int64_t integer;
            double floating;
            bool boolean;
            Object *object;
        } as;

        Value();            // 1
        Value(int64_t val); // 2
        Value(double val);  // 3
        Value(bool val);    // 4
        Value(Object *obj); // 5

        // this equals operator is only used for internals, not actual comparisons.
        bool operator==(Value const &val);
        bool is_obj_type(ObjectType type);

        Value &operator=(bool b);           // 1
        Value &operator=(double val);       // 2
        Value &operator=(int64_t val);      // 3
        Value &operator=(Object *obj);      // 4
        
        Value(Value const &) = default;
        Value &operator=(Value const &val) = default;

        std::string to_string() const;
    };

    std::ostream &operator<<(std::ostream &out, Value const &val);

}

#endif