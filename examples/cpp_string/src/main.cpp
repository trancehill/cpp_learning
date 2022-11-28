#include <cstdio>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> result;
    
    size_t prev = 0;
    size_t pos = str.find(delim);

    while(pos != std::string::npos)
    {
        result.emplace_back(str.substr(prev, pos));
        prev = pos+1;
        pos = str.find(delim, prev);
    }

    if(prev < str.size())
    { result.emplace_back(str.substr(prev)); }

    return result;
}

int main(int argc, char** argv)
{
    std::string str(argv[1]);
    std::string str1(argv[2]);

    //equals
    if(str == "test_string")
    { puts("str is a test_string"); }

    //iterate
    for(auto it = str.begin(); it != str.end(); ++it)
    {
        printf("%c", *it);
    }
    printf("\n");

    for(auto c : str)
    {
        printf("%c", c);
    }
    printf("\n");

    //contains
    size_t pos = str.find(str1);
    if(pos != std::string::npos)
    {
        //substr
        printf("str contains %s\n", str.substr(pos, str1.size()).c_str());
    }

    //split
    for(const auto& part: split(str, ","))
    {
        printf("%s\n", part.c_str());
    }

    //starts_with,ends_with
    if(str.find("start") == 0)
    {
        puts("starts with start");
    }

    if(str.find("end") == (str.size() - std::string("end").size()) )
    {
        puts("ends with end");
    }

    //erase from middle
    size_t str_idx = 0; 
    for(auto it = str.begin(); it != str.end();)
    {
        if(str_idx == str.size() / 2)
        { it = str.erase(it); }
        else
        { ++it; }
    }

    return 0;
}