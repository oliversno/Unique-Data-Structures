#ifndef RA_ITER_H
#define RA_ITER_H
#include <cstddef> // ptrdiff_t
#include <type_traits> // remove_cv
#include <iterator>

template < class T, class UnquaifiedT = std::remove_cv_t<T> >
class RAIterator : public std::iterator<std::random_access_iterator_tag,
                                        UnquaifiedT,
                                        std::ptrdiff_t,
                                        T*,
                                        T&>
{
protected:
    UnquaifiedT* m_ptr;
public:
    RAIterator(UnquaifiedT* ptr = nullptr) : m_ptr(ptr) {}
    ~RAIterator(){}

    RAIterator<T>& operator=(const RAIterator<T>& iter) = default;

    operator bool() const{
        if(m_ptr)
            return true;
        return false;
    }
    bool operator==(const RAIterator<T>& rhs) const{ return m_ptr == rhs.getConstPtr(); }
    bool operator!=(const RAIterator<T>& rhs) const{ return m_ptr != rhs.getConstPtr(); }
    RAIterator<T>& operator+=(const int& mov){ m_ptr += mov; return *this; }
    RAIterator<T>& operator-=(const int& mov){ m_ptr -= mov; return *this; }
    RAIterator<T>& operator++(){ ++m_ptr; return *this; }
    RAIterator<T>& operator--(){ --m_ptr; return *this; }
    RAIterator<T>& operator++(int){ auto temp{*this}; ++m_ptr; return temp; }
    RAIterator<T>& operator--(int){ auto temp{*this}; --m_ptr; return temp; }
    RAIterator<T>& operator+(const int& mov){
        auto old_ptr = m_ptr;
        m_ptr += mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    RAIterator<T>& operator-(const int& mov){
        auto old_ptr = m_ptr;
        m_ptr -= mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    int operator-(const RAIterator<T>& rhs) { return std::distance(rhs.getPtr(), this->getPtr()); }
    T& operator*(){ return *m_ptr; }
    const T& operator*() const{ return *m_ptr; }
    T* operator->(){ return m_ptr; }
    T* getPtr(){ return m_ptr; }
    const T* getConstPtr() const{ return m_ptr; }
    void swap(RAIterator<T>& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
    }
};

#endif