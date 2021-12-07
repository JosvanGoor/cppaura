#include "utility.ih"

char *aura::read_file(char const *filename)
{
    ifstream in(filename);

    if (!in)
    {
        cerr << "Failed to open file \"" << filename << "\"\n";
        exit(-2);
    }

    char *buffer = nullptr;

    in.seekg(0, ios::end);
    size_t size = in.tellg();
    buffer = new char[size + 1];
    in.seekg(0, ios::beg);

    in.read(buffer, size);
    buffer[size] = '\0';
    return buffer;
}