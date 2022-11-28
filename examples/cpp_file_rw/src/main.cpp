#include <cstdio>
#include <cstring>
#include "file.h"

int main(int argc, char** argv)
{

    std::string str = "This is a test!\n";
    std::string str2 = "This is a test2!\n";
    std::string str3 = "This is a test3!\n";
    
    std::vector<uint8_t> v_data1(str2.size());
    memcpy(v_data1.data(), str2.c_str(), str2.size());

    std::vector<uint8_t> v_data2(str3.size());
    memcpy(v_data2.data(), str3.c_str(), str3.size());

    io::File file("testy.txt", "w+");
    if(!file)
    {
        printf("OPEN ERROR: %i\n", file.error());
    }
    else
    {

        if(file.write(str) != str.size())
        {
            printf("STR WRITE ERROR: %i\n", file.error());
            return 1;
        }
        printf("String write success!\n");
        
        file.seekFromBegin(0);
        std::vector<uint8_t> r_data = file.read(str.size());
        if(r_data.size() == 0)
        {
            printf("Read error: %i\n", file.error());
            return 1;
        }

        if(file.write(v_data1) != v_data1.size())
        {
            printf("Vector write error: %i\n", file.error());
            return 1;
        }
        printf("Vectory write OK!\n");

        if(file.write(v_data2.data(), v_data2.size()) != v_data2.size())
        {
            printf("Pointer + size write error: %i\n", file.error());
            return 1;
        }
        printf("Pointer + size write OK!\n");

        file.seekFromBegin(0);

        std::string line1 = file.readLine();
        printf("%s\n", line1.c_str());



        //if(file.write(v_data) != v_data.size())
        //{
        //    printf("%i", file.error());
        //}


        //file.write(v_data.data(), v_data.size());

        return 0;
    }
}