// Írj egy LinkedList nevű osztályt, mely uint32_t típusú értékeket tárolhat és a következő függvényekkel rendelkezik.
// add - beszúr egy elemet a végére
// size - visszaadja mennyi elem van a LinkedList -ben
// at(idx) - visszaad egy elemet a megadott idx -en
// insert(idx) - beszúr egy elemet az adott indexre
// current() - visszaad egy aktuális elemet, amire egy belső cursor mutat
// next() - lépteti a belső cursor -t a következő elemre
// prev() - lépteti a belső cursor -t az előző elemre

#include <cstdio>
#include "stdint.h"

class LinkedList
{
public:
    struct Elem
    {
        uint32_t data;
        Elem* next;
        Elem* prev;

        Elem(uint32_t _data, Elem* _prev) : data(_data), next(nullptr), prev(_prev) {}
    };

    LinkedList();
    ~LinkedList();

    void add(uint32_t value);
    void remove(size_t idx);

    size_t size();

    uint32_t at(size_t idx);

    void insert(size_t idx, uint32_t value);

    uint32_t current();
    uint32_t next();
    uint32_t prev();
    void reset();

    void clear();

private:
    Elem* mFirst;
    size_t mSize;

    Elem* mCursor;

    Elem* get_elem(size_t idx);
};