#include <iterator>
#include <cstddef> // ptrdiff_t
#include "include/RevIterator.h"
template <typename T>
RevIterator<T>& RevIterator<T>::operator=(T* ptr){ m_ptr = ptr; return *this; }
template <typename T>
RevIterator<T>::operator bool() const{
    if(m_ptr)
        return true;
    return false;
}
template <typename T>
bool RevIterator<T>::operator==(const RevIterator<T>& rhs) const{ return m_ptr == rhs.getConstPtr(); }
template <typename T>
bool RevIterator<T>::operator!=(const RevIterator<T>& rhs) const{ return m_ptr != rhs.getConstPtr(); }
template <typename T>
RevIterator<T>& RevIterator<T>::operator+=(const int& mov){ m_ptr -= mov; return *this; }
template <typename T>
RevIterator<T>& RevIterator<T>::operator-=(const int& mov){ m_ptr += mov; return *this; }
template <typename T>
RevIterator<T>& RevIterator<T>::operator++(){ --m_ptr; return *this; }
template <typename T>
RevIterator<T>& RevIterator<T>::operator--(){ ++m_ptr; return *this; }
template <typename T>
RevIterator<T>& RevIterator<T>::operator++(int){ auto temp{*this}; --m_ptr; return temp; }
template <typename T>
RevIterator<T>& RevIterator<T>::operator--(int){ auto temp{*this}; ++m_ptr; return temp; }
template <typename T>
RevIterator<T>& RevIterator<T>::operator+(const int& mov){
    auto old_ptr = m_ptr;
    m_ptr -= mov;
    auto temp{*this};
    m_ptr = old_ptr;
    return temp;    
}
template <typename T>
RevIterator<T>& RevIterator<T>::operator-(const int& mov){
    auto old_ptr = m_ptr;
    m_ptr += mov;
    auto temp{*this};
    m_ptr = old_ptr;
    return temp;    
}
template <typename T>
int RevIterator<T>::operator-(const RevIterator<T>& rhs) { return std::distance(rhs.getPtr(), this->getPtr()); }
template <typename T>
RAIterator<T> RevIterator<T>::base(){
    RAIterator<T> forwardIt{this->m_ptr};
    ++forwardIt;
    return forwardIt;
}    