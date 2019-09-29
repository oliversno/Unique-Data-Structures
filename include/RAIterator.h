#include <iterator>
#include <cstddef> // ptrdiff_t
template <typename T> 
class RAIterator : public std::iterator<std::random_access_iterator_tag,
                                                T,
                                                std::ptrdiff_t,
                                                T*,
                                                T&>
        {
        protected:
            T* m_ptr;
        public:
            RAIterator(T* ptr = nullptr) : m_ptr(ptr) {}
            ~RAIterator(){}

            RAIterator& operator=(T* ptr);

            operator bool() const;
            template<class OtherType>
            bool operator==(const RAIterator& rhs) const;
            template<class OtherType>
            bool operator!=(const RAIterator& rhs) const;
            RAIterator& operator+=(const int& mov);
            RAIterator& operator-=(const int& mov);
            RAIterator& operator++();
            RAIterator& operator--();
            RAIterator operator++(int);
            RAIterator operator--(int);
            RAIterator& operator+(const int& mov);
            RAIterator& operator-(const int& mov);
            int operator-(const RAIterator& rhs);
            T& operator*();
            const T& operator*() const;
            T* operator->();
            T* getPtr();
            void swap(RAIterator& other) noexcept;
            const T* getConstPtr() const;
        };