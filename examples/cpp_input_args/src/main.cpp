#include <cstdio>
#include "argparse.h"


int main(int argc, char** argv)
{
    ArgParse parser(argc, argv);
    if(parser.count() == 0 || parser.hasFlag("-h", "--help"))
    {
        printf("Usage: %s\n", parser.getName().c_str());
        return 0;
    }

    if(auto integer = parser.getInt("-i", "--integer"))
    {
        printf("Integer arg: %ld\n", integer.value);
    }

    if(auto fp = parser.getDouble("-d", "--double"))
    {
        printf("Double arg: %lf\n", fp.value);
    }

    auto str = parser.getStr("-s", "--string");
    if(!str.empty())
    {
        printf("String arg: %s\n", str.c_str());
    }

    return 0;
}
