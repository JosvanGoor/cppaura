// #include "virtualmachine.ih"

// void VirtualMachine::concatenate(Value const &lhs, Value const &rhs)
// {
//     string left = lhs.to_string();
//     ObjString *right = reinterpret_cast<ObjString*>(rhs.as.object);

//     size_t newlen = left.size() + right->length;
//     char *newchars = reinterpret_cast<char*>(allocate(sizeof(char) * (newlen + 1)));
//     memcpy(newchars, left.c_str(), left.size());
//     memcpy(newchars + left.size(), right->chars, right->length);
//     newchars[newlen] = '\0';

//     peek(0) = take_string(newchars, newlen);
// }