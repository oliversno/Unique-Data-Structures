#ifndef REV_ITER_H
#define REV_ITER_H
#include "BD_Iter.h"

template <typename T>
class RevIterator : public BDIterator<T>
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
    RevIterator<T>& operator+=(const ptrdiff_t& mov){ m_ptr -= mov; return *this; }
    RevIterator<T>& operator-=(const ptrdiff_t& mov){ m_ptr += mov; return *this; }
    RevIterator<T>& operator++(){ --m_ptr; return *this; }
    RevIterator<T>& operator--(){ ++m_ptr; return *this; }
    RevIterator<T>& operator++(ptrdiff_t){ auto temp{*this}; --m_ptr; return temp; }
    RevIterator<T>& operator--(ptrdiff_t){ auto temp{*this}; ++m_ptr; return temp; }
    RevIterator<T>& operator+(const ptrdiff_t& mov){
        auto old_ptr = m_ptr;
        m_ptr -= mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    RevIterator<T>& operator-(const ptrdiff_t& mov){
        auto old_ptr = m_ptr;
        m_ptr += mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    ptrdiff_t operator-(const RevIterator<T>& rhs) { return std::distance(rhs.getPtr(), this->getPtr()); }

    BDIterator<T> base(){
        BDIterator<T> forwardIt{this->m_ptr};
        ++forwardIt;
        return forwardIt;
    }    
};

#endif