#include <cstdio>
#include "linked_list.h"

int main(int argc, char** argv)
{

    LinkedList list;

    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.insert(0, 5);

    printf("size: %lu\n", list.size());

    //printf("%u\n", list.at(4));

    for(size_t i=0; i < list.size(); ++i)
    {
        printf("idx %lu\n", i);
        printf("value: %u\n", list.at(i));
    }

    return 0;


    list.remove(3);


    printf("size: %lu\n", list.size());
    for(size_t i=0; i < list.size(); ++i)
    {
        printf("idx %lu: %u\n", i, list.at(i));
    }



    return 0;
}