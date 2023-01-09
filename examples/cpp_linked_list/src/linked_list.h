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

    /**
     * Append a new entry to the end of the list
     * 
     * @param value Number to add
    **/
    void add(uint32_t value);

    /**
     * Remove the entry at the given index from the list
     * 
     * @param idx Index of entry to remove
    **/
    void remove(size_t idx);

    /**
     * Get the number of entries in the list
    **/
    size_t size();

    /**
     * Get the value of the entry at the given index
     * 
     * @param idx Index to get value from
     * @return Value at index
    **/
    uint32_t at(size_t idx);

    /**
     * Insert a new entry at the given index
     * 
     * @param idx Where to insert the new value, if idx is larger than the list size, appends to the end
     * @param value Number to insert
    **/
    void insert(size_t idx, uint32_t value);

    /**
     * Get the value from the current cursor position
    **/
    uint32_t current();

    /**
     * Move the cursor to the next index and returns its value 
    **/
    uint32_t next();

    /**
     * Move the cursor to the previous index and returns its value 
    **/
    uint32_t prev();

    /**
     * Reset the cursor to the start of the list
    **/
    void reset();

    /**
     * Remove every element from the list
    **/
    void clear();

private:
    Elem* mFirst;
    size_t mSize;

    Elem* mCursor;

    Elem* get_elem(size_t idx);
};