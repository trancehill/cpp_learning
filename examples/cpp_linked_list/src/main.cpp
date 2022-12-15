#include <cstdio>
#include "linked_list.h"

int main(int argc, char** argv)
{

    LinkedList list;

    list.add(1);
    list.add(2);
    list.add(3);
    list.insert(1, 4);

    printf("size: %lu\n", list.size());
    printf("idx 0: %u\n", list.at(0));
    printf("idx 1: %u\n", list.at(1));
    printf("idx 2: %u\n", list.at(2));
    printf("idx 3: %u\n", list.at(3));

    list.remove(3);

    printf("size: %lu\n", list.size());
    printf("idx 0: %u\n", list.at(0));
    printf("idx 1: %u\n", list.at(1));
    printf("idx 2: %u\n", list.at(2));



    return 0;
}