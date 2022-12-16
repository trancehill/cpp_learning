#include "linked_list.h"

LinkedList::LinkedList() 
    : mFirst(nullptr)
    , mSize(0)
    , mCursor(mFirst)
{}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::add(uint32_t value)
{
    Elem* cursor = mFirst;

    if (cursor == nullptr)
    {
        mFirst = new Elem(value);
    }
    else
    {
        while (cursor->next != nullptr)
        {
            cursor = cursor->next;
        }

        cursor->next = new Elem(value);
    }

    ++mSize;
}

void LinkedList::remove(size_t idx)
{
    if(idx < mSize)
    {
        if(idx == 0)
        {
            Elem* removed = mFirst;
            mFirst = removed->next;

            delete removed;
        }
        else
        {
            size_t counter = 0;

            Elem* prev_cursor = mFirst;
            Elem* cursor = mFirst;

            while(counter != idx)
            {
                prev_cursor = cursor;
                cursor = cursor->next;
                ++counter;
            }
        
            prev_cursor->next = cursor->next;

            delete cursor;
        }

        --mSize;
    }
}

uint32_t LinkedList::at(size_t idx)
{
    uint32_t result = 0;

    if (idx < mSize)
    {
        Elem* cursor = get_elem(idx);
        result = cursor->data;
    }

    return result;
}

void LinkedList::insert(size_t idx, uint32_t value)
{
    if(idx < mSize)
    {
        if(idx == 0)
        {
            Elem* next_value = mFirst;
            mFirst = new Elem(value);
            mFirst->next = next_value;
        }
        else
        {
            Elem* cursor = get_elem(idx-1);
            Elem* next_value = cursor->next;

            cursor->next = new Elem(value);
            cursor->next->next = next_value;
        }

        ++mSize;
    }
    else
    {
        add(value);
    }
}

size_t LinkedList::size()
{
    return mSize;
}

uint32_t LinkedList::current()
{
    return mCursor->data;
}
uint32_t LinkedList::next()
{
    mCursor = mCursor->next;

    return current();
}

void LinkedList::clear()
{
    Elem* cursor = mFirst;

    while (cursor->next != nullptr)
    {
        Elem* first = cursor;
        cursor = cursor->next;
        delete first;
    }

    if(cursor != nullptr)
    {
        delete cursor;
    }

    mFirst = nullptr;
}

LinkedList::Elem* LinkedList::get_elem(size_t idx)
{
    Elem* cursor = mFirst;
    size_t counter = 0;

    while (counter != idx)
    {
        printf("first: %p, cursor: %p, cnt: %lu, idx: %lu\n", mFirst, cursor, counter, idx);
        cursor = cursor->next;
        printf("next: %p\n", cursor);
        ++counter;
    }

    return cursor;
}