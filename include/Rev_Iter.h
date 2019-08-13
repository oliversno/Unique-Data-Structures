#ifndef REV_ITER_H
#define REV_ITER_H
#include "RA_Iter.h"

template <typename T>
class RevIterator : public RAIterator<T>
{
protected:
    T* m_ptr;
public:
    RevIterator(T* ptr = nullptr) : m_ptr(ptr){}
    RevIterator(const RevIterator<T>& iter) = default;
    ~RevIterator(){}

    RevIterator<T>& operator=(const RevIterator<T>& iter) = default;
    RevIterator<T>& operator=(T* ptr){ m_ptr = ptr; return *this; }

    operator bool() const{
        if(m_ptr)
            return true;
        return false;
    }
    bool operator==(const RevIterator<T>& rhs) const{ return m_ptr == rhs.getConstPtr(); }
    bool operator!=(const RevIterator<T>& rhs) const{ return m_ptr != rhs.getConstPtr(); }
    RevIterator<T>& operator+=(const int& mov){ m_ptr -= mov; return *this; }
    RevIterator<T>& operator-=(const int& mov){ m_ptr += mov; return *this; }
    RevIterator<T>& operator++(){ --m_ptr; return *this; }
    RevIterator<T>& operator--(){ ++m_ptr; return *this; }
    RevIterator<T>& operator++(int){ auto temp{*this}; --m_ptr; return temp; }
    RevIterator<T>& operator--(int){ auto temp{*this}; ++m_ptr; return temp; }
    RevIterator<T>& operator+(const int& mov){
        auto old_ptr = m_ptr;
        m_ptr -= mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    RevIterator<T>& operator-(const int& mov){
        auto old_ptr = m_ptr;
        m_ptr += mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    int operator-(const RevIterator<T>& rhs) { return std::distance(rhs.getPtr(), this->getPtr()); }

    RAIterator<T> base(){
        RAIterator<T> forwardIt{this->m_ptr};
        ++forwardIt;
        return forwardIt;
    }    
};

#endif