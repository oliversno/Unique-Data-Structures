#include <iterator>
#include <cstddef> // ptrdiff_t
#include "include/RAIterator.h"

template <typename T>
RAIterator<T>& RAIterator<T>::operator=(T* ptr){ m_ptr = ptr; return *this; }
template <typename T>
RAIterator<T>::operator bool() const{
    if(m_ptr)
        return true;
    return false;
}
template <typename T>
template<class OtherType>
bool RAIterator<T>::operator==(const RAIterator<T>& rhs) const{ return m_ptr == rhs.m_ptr; }
template <typename T>
template<class OtherType>
bool RAIterator<T>::operator!=(const RAIterator<T>& rhs) const{ return m_ptr != rhs.m_ptr; }
template <typename T>
RAIterator<T>& RAIterator<T>::operator+=(const int& mov){ m_ptr += mov; return *this; }
template <typename T>
RAIterator<T>& RAIterator<T>::operator-=(const int& mov){ m_ptr -= mov; return *this; }
template <typename T>
RAIterator<T>& RAIterator<T>::operator++(){ ++m_ptr; return *this; }
template <typename T>
RAIterator<T>& RAIterator<T>::operator--(){ --m_ptr; return *this; }
template <typename T>
RAIterator<T> RAIterator<T>::operator++(int){ auto temp{*this}; ++m_ptr; return temp; }
template <typename T>
RAIterator<T> RAIterator<T>::operator--(int){ auto temp{*this}; --m_ptr; return temp; }
template <typename T>
RAIterator<T>& RAIterator<T>::operator+(const int& mov){
    auto old_ptr = m_ptr;
    m_ptr += mov;
    auto temp{*this};
    m_ptr = old_ptr;
    return temp;    
}
template <typename T>
RAIterator<T>& RAIterator<T>::operator-(const int& mov){
    auto old_ptr = m_ptr;
    m_ptr -= mov;
    auto temp{*this};
    m_ptr = old_ptr;
    return temp;    
}
template <typename T>
int RAIterator<T>::operator-(const RAIterator<T>& rhs) { return std::distance(rhs.getConstPtr(), this->getConstPtr()); }
template <typename T>
T& RAIterator<T>::operator*(){ return m_ptr->element; }
template <typename T>
const T& RAIterator<T>::operator*() const{ return m_ptr->element; }
template <typename T>
T* RAIterator<T>::operator->(){ return &m_ptr->element; }
template <typename T>
T* RAIterator<T>::getPtr(){ return m_ptr;}
template <typename T>
void RAIterator<T>::swap(RAIterator<T>& other) noexcept
{
    std::swap(m_ptr, other.m_ptr);
}
template <typename T>
const T* RAIterator<T>::getConstPtr() const{return m_ptr; }