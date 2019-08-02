#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "BD_Iter.h"
#include "Rev_Iter.h"
#include <algorithm>

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
        typedef BDIterator<T> iterator;
        typedef BDIterator<const T> const_iterator;
        typedef RevIterator<T> reverse_iterator;
        typedef RevIterator<const T> const_reverse_iterator;
        // ctors
        SkipList() : num_layers(0), size(0){
            head = make_node(kMAX_LAYERS, 0);
        }
        SkipList(unsigned int count, const T& value){
            this = new SkipList;
            for(unsigned int i = 0; i < count; ++i){
                push_back(value);
            }
        }
        template <class InputIt>
        SkipList(InputIt first, InputIt last){
            this = new SkipList;
            for(auto it = first; it != last; ++it){
                push_back(*it);
            }
        }
        SkipList(const SkipList& other) : size(other.size()), num_layers(other.num_layers) {
            head = new Node;
            *head = *other.head;
        }
        SkipList(const SkipList&& other) : size(other.size(), num_layers(other.num_layers()) {
            head = other.head;
            other.head = nullptr;
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
        SkipList& operator=(const SkipList&& other) : size(other.size()), num_layers(other.num_layers()) {
            if(&other == this){
                return *this;
            }
            delete head;
            head = other.head;
            other.head = nullptr;
            return *this;
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
        iterator begin(){ return iterator(head);}
        const_iterator begin() const { return cbegin(); }
        const_iterator cbegin() const{ return const_iterator(head);}
        iterator end(){
            Node* cur_ptr = head->forawrd[num_layers];
            while(cur_ptr){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return iterator(cur_ptr);
        }
        const_iterator end() const { return cend(); }
        const_iterator cend() const{
            Node* cur_ptr = head->forward[num_layers];
            while(cur_ptr){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return const_iterator(cur_ptr);
        }
        reverse_iterator rbegin(){
            Node* cur_ptr = head;
            while(cur_ptr->forward[num_layers]){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return reverse_iterator(cur_ptr);
        }
        const_reverse_iterator rbegin() const{ return crbegin(); }
        const_reverse_iterator crbegin() const{
            Node* cur_ptr = head;
            while(cur_ptr->forward[num_layers]){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return const_reverse_iterator(cur_ptr);
        }
        reverse_iterator rend(){ return everse_iterator(head-1); }
        const_reverse_iterator rend() const{ return crend(); }
        const_reverse_iterator crend() const{ return const_reverse_iterator(head-1); }

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
        std::pair<iterator, bool> insert(const T& value){
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
        std::pair<iterator, bool> insert(T&& value);
        iterator insert(const_iterator pos, const T& value);
        iterator insert(const_iterator pos, T&& value){
            //use pos as hint
        }
        iterator insert(const_iterator pos, size_t count, const T& value);
        template <class InputIt);
        void insert(iterator pos, InputIt first, InputIt last){
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
        std::pair<iterator, bool> emplace(const_iterator pos, Args&&... args);
        iterator emplace(const_iterator pos, Args&&... args);
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
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last){
            auto it = last;
            while(it != first){
                auto res = erase(it--);
            }
            return res;
        }
        void swap(SkipList& other){
            if(this != &other) {
                std::swap(this->num_layers, other->num_layers);
                std::swap(this->size, other->size);
                std::swap(this->head, other->head);
            }
        }

        // lookup
        size_t count(const T& value) const{
            auto pair = equal_range(value);
            return std::distence(pair.second - pair.first);
        }
        iterator find(const T& value){
            Node* cur_ptr = head;
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->element < value){
                    if(cur_ptr->element == value)
                        return //ptr to iterator
                    cur_ptr = cur_ptr->forward[i];
                }
            }
            return this->end();
        }
        const_iterator find(const T& value) const;
        bool contains(const T& value) const{
            return find(value) != this->end();
        }
        std::pair<iterator, iterator> equal_range(const T& value){
            auto start_it = find(value);
            Node* cur_ptr = start_it;
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr-forward[i] && cur_ptr->element <= value){
                    cur_ptr = cur_ptr->forward[i];
                }
            }
            iterator end_it = cur_ptr;
            return std::make_pair(start_it, end_it);
        }
        std::pair<const_iterator, const_iterator> equal_range(const T& value) const;
        iterator lower_bound(const T& value){
            return equal_range(value).second->forward[0];
        }
        const_iterator lower_bound(const T& value) const{
            return equal_range(value).second->forward[0];
        }
        iterator upper_bound(const T& value);
        const_iterator upper_bound(const T& value) const;
        // operations
        void merge(SkipList& other);
        void merge(SkipList&& other);
        template <class Compare >
        void merge(SkipList& other, Compare comp);
        template <class Compare >
        void merge(SkipList&& other, Compare comp);
        void splice(const_iterator pos, SkipList& other);
        void splice(const_iterator pos, SkipList&& other);
        void splice(const_iterator pos, SkipList& other, const_iterator it);
        void splice(const_iterator pos, SkipList&& other, const_iterator it);
        void splice(const_iterator pos, SkipList& other, const_iterator first, const_iterator last);
        void splice(const_iterator pos, SkipList&& other, const_iterator first, const_iterator last);
        void remove(const T& value){
            for(auto it = this->begin(), last = this->end(); it != last){
                if(*it == U){
                    it = this->erase(it);
                }
                else{
                    ++it;
                }
            }
        }
        template <class UnaryPred>
        void remove_if(UnaryPred p){
            for(auto it = this->begin(), last = this->end(); it != last){
                if(pred(*it)){
                    it = erase(it);
                }
                else{
                    ++it;
                }
            }
        }
        template <class UnaryPred>
        size_t remove_if(UnaryPred p){
            remove_if(p);
            return size;
        }
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
void swap(SkipList<T>& lhs, SkipList<T>& rhs){
    lhs.swap(rhs);
}
template <class T, class U>
void erase(SkipList<T>& c, const U& value){
    c.remove(value);
}
template <class T, class Pred>
void erase_if(SkipList<T>& c, Pred pred){
    c.remove_if(pred);
}

#endif