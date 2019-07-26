#ifndef SKIP_LIST_H
#define SKIP_LIST_H

template <class T>
class SkipList{
    private:
        static const float kPROMOTION_PROB = 0.5;
        static const uint32 kMAX_LAYERS = 6;
        uint32 num_layers;
        uint32 size;
        Node* head;
        struct Node{
            T element;
            Node* next[num_layers];
            Node* previous[num_layers];
        };
        Node* make_node(const uint32 level, const T& value) const{
            Node* node = new Node;
            node->element = value;
        }
    public:
        // ctors
        SkipList() : num_layers(0), size(0){
            head = make_node(kMAX_LAYERS, 0);
        }
        SkipList(uint32 count, const T& value = T()){
            SkipList;
            for(uint32 i = 0; i < count; ++i){
                push_back(value);
            }
        }
        SkipList(uint32 count, const T& value){
            SkipList(count, value);
        }
        template <class InputIt>
        SkipList(InputIt first, InputIt last){
            SkipList;
            for(auto it = first; it != last; ++it){
                push_back(*it);
            }
        }
        SkipList(const SkipList& other) : size(other.size()), num_layers(other.num_layers) {
            if(!other.empty()){
                Node* other_ptr = other.head;
                Node* ptr = new Node{other_ptr->element, nullptr, nullptr};
                head = ptr;
                while(other_ptr->next[0]){
                    other_ptr = other_ptr->next[0];
                    Node* next = new Node{other_ptr->element, ptr, nullptr};
                    ptr->next[0] = next;
                    ptr = ptr->next[0]
                }
        }
        SkipList(const SkipList&& other){
            //TODO
        }
        SkipList(std::initilizer_list<T> ilist){
            //TODO
        }

        // dtor
        ~SkipList(){
            //TODO
        }

        // assignment operators
        SkipList& operator=(const SkipList& other){
            swap(other);
        }
        SkipList& operator=(const SkipList&& other){
            //TODO
        }
        SkipList& operator=(std::initilizer_list<T> ilist){
            //TODO
        }

        // element access
        T& front(){
            return head->element;
        }
        const T& front() const{
            return head->element;
        }
        T& back(){
            Node* ptr = head;
            while(ptr->next[0]){
                ptr = ptr->next[0];
            }
            return ptr->element;
        }
        const T& back() const{
            Node* ptr = head;
            while(ptr->next[0]){
                ptr = ptr->next[0];
            }
            return ptr->element;
        }

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
        bool empty() const{
            return size == 0;
        }
        size_t size() const{
            return size;
        }
        size_t max_size() const{
            //TODO
        }

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