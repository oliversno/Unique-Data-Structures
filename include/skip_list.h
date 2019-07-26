#ifndef SKIP_LIST_H
#define SKIP_LIST_H

template <class T>
class SkipList{
    private:
        uint32 promotion_prob;
        uint32 num_layers;
        Node* head;
        class Node{
            private:
                T element;
                Node* next[num_layers];
                Node* previous[num_layers];
        };
    public:
        // ctors
        SkipList();
        SkipList(uint32 count, const T& value = T());
        SkipList(uint32 count, const T& value);
        template <class InputIt>
        SkipList(InputIt first, InputIt, last);
        SkipList(const SkipList& other);
        SkipList(const SkipList&& other);
        SkipList(std::initilizer_list<T> ilist);

        // dtor
        ~SkipList();

        // assignment operators
        SkipList& operator=(const SkipList& other);
        SkipList& operator=(const SkipList&& other);
        SkipList& operator=(std::initilizer_list<T> ilist);

        // element access
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // iterators
        SkipList::iterator begin();
        SkipList::const_iterator begin() const;
        SkipList::const_iterator cbegin() const;
        SkipList::iterator end();
        SkipList::const_iterator end() const;
        SkipList::const_iterator cend() const;
        SkipList::reverse_iterator rbegin();
        SkipList::const_reverse_iterator rbegin() const;
        SkipList::const_reverse_iterator crbegin() const;
        SkipList::reverse_iterator rend();
        SkipList::const_reverse_iterator rend() const;
        SkipList::const_reverse_iterator crend() const;

        // capacity
        bool empty() const;
        size_t size() const;
        size_t max_size() const;

        // modifiers
        void clear();
        SkipList::iterator insert(SkipList::iterator pos, const T& value);
        SkipList::iterator insert(SkipList::const_iterator pos, const T& value);
        SkipList::iterator insert(SkipList::const_iterator pos, T&& value);
        void insert(SkipList::iterator pos, size_t count, const T& value);
        SkipList::iterator insert(SkipList::const_iterator pos, size_t count, const T& value);
        template <class InputIt);
        void insert(SkipList::iterator pos, InputIt first, InputIt last);
        SkipList::iterator insert(SkipList::const_iterator pos, InputIt first, InputIt last);
        SkipList::iterator insert(SkipList::const_iterator pos, std::initilizer_list<T> ilist);
        template <class... Args>
        SkipList::iterator emplace(SkipList::const_iterator pos, Args&&... args);
        SkipList::iterator erase(SkipList::iterator pos);
        SkipList::iterator erase(SkipList::const_iterator pos);
        SkipList::iterator erase(SkipList::iterator first, SkipList::iterator last);
        SkipList::iterator erase(SkipList::const_iterator first, SkipList::const_iterator last);
        void push_back(const T& value);
        void push_back(T&& value);
        template <class... Args>
        void emplace_back(Args&&... args);
        template <class... Args>
        T& emplace_back(Args&&... args);
        void pop_back();
        void push_front(const T& value);
        void push_front(T&& value);
        template <class... Args>
        void emplace_front(Args&&... args);
        template <class... Args>
        T& emplace_front(Args&&... args);
        void pop_front();
        void resize(size_t count, T value = T());
        void resize(size_t count);
        void resize(size_t count, const &T value);
        void swap(SkipList& other);

        // operations
        void merge(SkipList& other);
        void merge(SkipList&& other);
        template <class Compare >
        void merge(SkipList& other, Compare comp);
        template <class Compare >
        void merge(SkipList&& other, Compare comp);
        void splice(SkipList::const_iterator pos, SkipList& other);
        void splice(SkipList::const_iterator pos, SkipList&& other);
        void splice(SkipList::const_iterator pos, SkipList& other, SkipList::const_iterator it);
        void splice(SkipList::const_iterator pos, SkipList&& other, SkipList::const_iterator it);
        void splice(SkipList::const_iterator pos, SkipList& other, SkipList::const_iterator first, SkipList::const_iterator last);
        void splice(SkipList::const_iterator pos, SkipList&& other, SkipList::const_iterator first, SkipList::const_iterator last);
        void remove(const T& value);
        template <class UnaryPred>
        void remove_if(UnaryPred p);
        template <class UnaryPred>
        size_t remove_if(UnaryPred p);
        void reverse();
        void unique();
        size_t unique();
        template <class BinaryPred>
        void unique(BinaryPred p);
        template <class BinaryPred>
        size_t unique(BinaryPred p);
        void sort();
        template <class Compare>
        void sort(Compare comp);
};

template <class T>
bool operator==(const SkipList<T>& lhs, const SkipList<T>& rhs);
template <class T>
bool operator!=(const SkipList<T>& lhs, const SkipList<T>& rhs);
template <class T>
bool operator<=(const SkipList<T>& lhs, const SkipList<T>& rhs);
template <class T>
bool operator<(const SkipList<T>& lhs, const SkipList<T>& rhs);
template <class T>
bool operator>=(const SkipList<T>& lhs, const SkipList<T>& rhs);
template <class T>
bool operator>(const SkipList<T>& lhs, const SkipList<T>& rhs);

template <class T>
void swap(SkipList<T>& lhs, SkipList<T>& rhs);
template <class T, class U>
void erase(SkipList<T>& c, const U& value);
template <class T, class Pred>
void erase_if(SkipList<T>& c, Pred pred);

#endif