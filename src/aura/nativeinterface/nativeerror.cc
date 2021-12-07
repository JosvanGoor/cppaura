#include "nativeinterface.ih"

void NativeInterface::native_error(char const *message)
{
    cout << "<Native error> " << message << "\n";
    d_native_ok = false;
}