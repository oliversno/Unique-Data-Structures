#ifndef RA_ITER_H
#define RA_ITER_H
#include <iterator>

template <typename T>
class RAIterator : public std::iterator<std::random_access_iterator_tag,
                                        T,
                                        int,
                                        T*,
                                        T&>
{
protected:
    T* m_ptr;
public:
    RAIterator(T* ptr = nullptr) : m_ptr(ptr){}
    RAIterator(const RAIterator<T>& iter) = default;
    ~RAIterator(){}

    RAIterator<T>& operator=(const RAIterator<T>& iter) = default;
    RAIterator<T>& operator=(T* ptr){ m_ptr = ptr; return *this; }

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
};

#endif