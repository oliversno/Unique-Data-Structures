#ifndef BD_ITER_H
#define BD_ITER_H
#include <iterator>

template <typename T>
class BDIterator : public std::iterator<std::bidirectional_iterator_tag,
                                        T,
                                        ptrdiff_t,
                                        T*,
                                        T&>
{
protected:
    T* m_ptr;
public:
    BDIterator(T* ptr = nullptr) : m_ptr(ptr){}
    BDIterator(const BDIterator<T>& iter) = default;
    ~BDIterator(){}

    BDIterator<T>& operator=(const BDIterator<T>& iter) = default;
    BDIterator<T>& operator=(T* ptr){ m_ptr = ptr; return *this; }

    operator bool() const{
        if(m_ptr)
            return true;
        return false;
    }
    bool operator==(const BDIterator<T>& rhs) const{ return m_ptr == rhs.getConstPtr(); }
    bool operator!=(const BDIterator<T>& rhs) const{ return m_ptr != rhs.getConstPtr(); }
    BDIterator<T>& operator+=(const ptrdiff_t& mov){ m_ptr += mov; return *this; }
    BDIterator<T>& operator-=(const ptrdiff_t& mov){ m_ptr -= mov; return *this; }
    BDIterator<T>& operator++(){ ++m_ptr; return *this; }
    BDIterator<T>& operator--(){ --m_ptr; return *this; }
    BDIterator<T>& operator++(ptrdiff_t){ auto temp{*this}; ++m_ptr; return temp; }
    BDIterator<T>& operator--(ptrdiff_t){ auto temp{*this}; --m_ptr; return temp; }
    BDIterator<T>& operator+(const ptrdiff_t& mov){
        auto old_ptr = m_ptr;
        m_ptr += mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    BDIterator<T>& operator-(const ptrdiff_t& mov){
        auto old_ptr = m_ptr;
        m_ptr -= mov;
        auto temp{*this};
        m_ptr = old_ptr;
        return temp;    
    }
    ptrdiff_t operator-(const BDIterator<T>& rhs) { return std::distance(rhs.getPtr(), this->getPtr()); }
    T& operator*(){ return *m_ptr; }
    const T& operator*() const{ return *m_ptr; }
    T* operator->(){ return m_ptr; }
    T* getPtr(){ return m_ptr; }
    const T* getConstPtr() const{ return m_ptr; }
};

#endif