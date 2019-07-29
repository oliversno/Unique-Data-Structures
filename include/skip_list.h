#ifndef SKIP_LIST_H
#define SKIP_LIST_H

template <class T>
class SkipList{
    private:
        static const float kPROMOTION_PROB = 0.5;
        static const unsigned int kMAX_LAYERS = 6;
        unsigned int num_layers;
        unsigned int size;
        Node* head;
        struct Node{
            T element;
            Node* forward[num_layers];
        };
        Node* make_node(const unsigned int level, const T& value) const{
            Node* node = new Node;
            node->element = value;
        }
    public:
        // ctors
        SkipList() : num_layers(0), size(0){
            head = make_node(kMAX_LAYERS, 0);
        }
        SkipList(unsigned int count, const T& value = T()){
            this = new SkipList;
            for(unsigned int i = 0; i < count; ++i){
                push_back(value);
            }
        }
        SkipList(unsigned int count, const T& value){
            SkipList(count, value);
        }
        template <class InputIt>
        SkipList(InputIt first, InputIt last){
            this = new SkipList;
            for(auto it = first; it != last; ++it){
                push_back(*it);
            }
        }
        SkipList(const SkipList& other) : size(other.size()), num_layers(other.num_layers) {
            if(!other.empty()){
                Node* other_ptr = other.head;
                Node* ptr = new Node{other_ptr->element, nullptr, nullptr};
                head = ptr;
                while(other_ptr->forward[0]){
                    other_ptr = other_ptr->forward[0];
                    Node* forward = new Node{other_ptr->element, ptr, nullptr};
                    ptr->forward[0] = forward;
                    ptr = ptr->forward[0]
                }
        }
        SkipList(const SkipList&& other){
            //TODO
        }
        SkipList(std::initilizer_list<T> ilist) : size(0), num_layers(0){
            auto it = ilist.begin();
            while(it != ilist.end()){
                insert(*it);
                ++it;
            }
        }

        // dtor
        ~SkipList(){
            //TODO
        }

        // assignment operators
        SkipList& operator=(const SkipList& other){
            swap(other);
            return *this;
        }
        SkipList& operator=(const SkipList&& other){
            //TODO
        }
        SkipList& operator=(std::initilizer_list<T> ilist){
            clear();
            *this = new SkipList(ilist);
            return *this;
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
            while(ptr->forward[0]){
                ptr = ptr->forward[0];
            }
            return ptr->element;
        }
        const T& back() const{
            Node* ptr = head;
            while(ptr->forward[0]){
                ptr = ptr->forward[0];
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
            unsigned int arch_bit = sizeof(void*)*8;
            return std::pow(2, arch_bit)/sizeof(T) - 1;
        }

        // modifiers
        void clear(){
            erase(this->begin(), this->end());
        }
        std::pair<SkipList::iterator, bool> insert(const T& value){
            Node* cur_ptr = head;
            // create an array to store changes on each layer
            Node* update[kMAX_LAYERS+1];
            memset(update, 0, sizeof(Node*)*(kMAX_LAYERS+1));
            //travel down layers and advance cur_ptr until right spot is found
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->forward[i]->element < value){
                    cur_ptr = cur_ptr->forward[i];
                }
                update[i] = cur_ptr;
            }
            cur_ptr = cur_ptr->forward[0]; // advance cur_ptr on bottom layer
            if(!cur_ptr || cur_ptr->element != value){
                unsigned int rand_layer = randomlevel();
                if(rand_layer > num_layers){
                    for(int i = num_layers+1; i < rand_layer+1; ++i){
                        update[i] = head;
                    }
                    num_layers = rand_layer
                }
                Node* new_node = new Node;
                new_node->element = value;
                for(int i = 0; i <= rand_layer; ++i){
                    new_node->forward[i] = update[i]->forward[i];
                    update[i]->forward[i] = new_node;
                }
                ++size;
                return std::make_pair(//new_node as it, true);
            }
            return std::make_pair(end(), false);
        }
        std::pair<SkipList::iterator, bool> insert(T&& value);
        SkipList::iterator insert(SkipList::const_iterator pos, const T& value);
        SkipList::iterator insert(SkipList::const_iterator pos, T&& value){
            //use pos as hint
        }
        SkipList::iterator insert(SkipList::const_iterator pos, size_t count, const T& value);
        template <class InputIt);
        void insert(SkipList::iterator pos, InputIt first, InputIt last){
            while(first != last){
                insert(pos++, value);
                ++first;
            }
        }
        void insert(std::initilizer_list<T> ilist){
            auto it = ilist.begin();
            while(it != ilist.end()){
                insert(*it);
                ++it;
            }
        }
        template <class... Args>
        std::pair<SkipList::iterator, bool> emplace(SkipList::const_iterator pos, Args&&... args);
        SkipList::iterator emplace(SkipList::const_iterator pos, Args&&... args);
        size_t erase(const T& value){
            Node* cur_ptr = head;
            // create an array to store changes on each layer
            Node* update[kMAX_LAYERS+1];
            memset(update, 0, sizeof(Node*)*(kMAX_LAYERS+1));
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->forward[i]->element < value){
                    cur_ptr = cur_ptr->forward[i];
                }
                update[i] = cur_ptr;
            }
            cur_ptr = cur_ptr->forward[0]; // advance cur_ptr on bottom layer
            if(cur_ptr && cur_ptr->element == value){
                for(int i = 0; i <= num_layers; ++i){
                    if(update[i]->forward[i] != cur_ptr)
                        break;
                    update[i]->forward[i] = cur_ptr->forward[i];
                }
                delete cur_ptr;
                while(num_layers > 0 && !head->forawrd[num_layers]){
                    --num_layers;
                }
                --size;
            }
            return size;
        }
        SkipList::iterator erase(SkipList::const_iterator pos);
        SkipList::iterator erase(SkipList::const_iterator first, SkipList::const_iterator last){
            auto it = last;
            while(it != first){
                auto res = erase(it--);
            }
            return res;
        }
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
};

template <class T>
bool operator==(const SkipList<T>& lhs, const SkipList<T>& rhs){
    if(lhs.size() != rhs.size()){return false; }
    auto lhs_it = lhs.begin();
    auto rhs_it = rhs.begin();
    while(lhs_it != lhs.end()){
        if(*lhs_it++ != *rhs_it++)
            return false;
    }
    return true;
}
template <class T>
bool operator!=(const SkipList<T>& lhs, const SkipList<T>& rhs){
    return !(lhs == rhs);
}
template <class T>
bool operator<=(const SkipList<T>& lhs, const SkipList<T>& rhs){
    return !(rhs<lhs);
}
template <class T>
bool operator<(const SkipList<T>& lhs, const SkipList<T>& rhs){
    return std::lexicographical_compare(lhs.begin(), lhs.end()
                                        rhs.begin(), rhs.end());
}
template <class T>
bool operator>=(const SkipList<T>& lhs, const SkipList<T>& rhs){
    return !(lhs<rhs);
}
template <class T>
bool operator>(const SkipList<T>& lhs, const SkipList<T>& rhs){
    return rhs<lhs;
}

template <class T>
void swap(SkipList<T>& lhs, SkipList<T>& rhs);
template <class T, class U>
void erase(SkipList<T>& c, const U& value){
        for(auto it = c.begin(), last = c.end(); it != last){
        if(*it == U){
            it = c.erase(it);
        }
        else{
            ++it;
        }
    }
}
template <class T, class Pred>
void erase_if(SkipList<T>& c, Pred pred){
    for(auto it = c.begin(), last = c.end(); it != last){
        if(pred(*it)){
            it = c.erase(it);
        }
        else{
            ++it;
        }
    }
}

#endif