#include <iterator>
#include <cstddef> // ptrdiff_t
#include "RAIterator.h"
template <typename T>
class RevIterator : public RAIterator<T>
{
protected:
    T* m_ptr;
public:
    RevIterator(T* ptr = nullptr) : m_ptr(ptr){}
    ~RevIterator(){}

    RevIterator& operator=(T* ptr);

    operator bool() const;
    bool operator==(const RevIterator& rhs) const;
    bool operator!=(const RevIterator& rhs) const;
    RevIterator& operator+=(const int& mov);
    RevIterator& operator-=(const int& mov);
    RevIterator& operator++();
    RevIterator& operator--();
    RevIterator& operator++(int);
    RevIterator& operator--(int);
    RevIterator& operator+(const int& mov);
    RevIterator& operator-(const int& mov);
    int operator-(const RevIterator& rhs);

    RAIterator<T> base();
};