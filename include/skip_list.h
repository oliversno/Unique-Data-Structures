#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "RA_Iter.h"
#include "Rev_Iter.h"
#include <algorithm>
#include <initializer_list>
#include <cmath>
#include <random>

template <class T,
          class Compare = std::less<T>,
          class Alloc = std::allocator<T>
          >
class SkipList{
    private:
        static constexpr float kPROMOTION_PROB = 0.5;
        static constexpr unsigned int kMAX_LAYERS = 6;
        unsigned int num_layers;
        unsigned int length;
        struct Node{
            T element;
            Node* forward[kMAX_LAYERS];
        };
        Node* head;
        Node* make_node(const unsigned int level, const T& value) const{
            Node* node = new Node;
            node->element = value;
        }
        void delete_node(Node* node){
            if(!node){
                delete_node(node->forward[0]);
                delete[] node->forward;
                for(int i = 0; i < num_layers; ++i){
                    node->forward[i] = nullptr;
                }
            }
        }
    unsigned int random_level(){
        std::random_device rd;
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<> distr{0.0, 1.0};
        unsigned int level = 0;
        while(distr(gen) < kPROMOTION_PROB && level < kMAX_LAYERS){
            ++level;
        }
        return level;
    }
    public:
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename std::allocator_traits<allocator_type>::pointer pointer;
        typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;
        typedef RAIterator<const value_type> iterator;
        typedef RAIterator<const value_type> const_iterator;
        typedef RevIterator<iterator> reverse_iterator;
        typedef RevIterator<const_iterator> const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type difference_type;

        // ctors
        SkipList() : num_layers(0), length(0){
            head = make_node(kMAX_LAYERS, 0);
        }
        template <class InputIt>
        SkipList(InputIt first, InputIt last){
            for(auto it = first; it != last; ++it){
                insert(*it);
            }
        }
        SkipList(const SkipList& other) : length(other.length()), num_layers(other.num_layers) {
            head = new Node;
            *head = *other.head;
        }
        SkipList(const SkipList&& other) : length(other.length()), num_layers(other.num_layers()) {
            head = other.head;
            other.head = nullptr;
        }
        SkipList(std::initializer_list<value_type> ilist) : length(0), num_layers(0){
            auto it = ilist.begin();
            while(it != ilist.end()){
                insert(*it);
                ++it;
            }
        }

        // dtor
        ~SkipList(){
            delete_node(head);
        }

        // assignment operators
        SkipList& operator=(const SkipList& other){
            if(&other == this){
                return *this;
            }
            length = other.length;
            num_layers = other.num_layers;
            delete head;
            head = other.head;
            other.head = nullptr;
            return *this;
        }
        SkipList& operator=(const SkipList&& other) {
            if(&other == this){
                return *this;
            }
            length = other.length;
            num_layers = other.num_layers;
            delete head;
            head = other.head;
            other.head = nullptr;
            return *this;
        }
        SkipList& operator=(std::initializer_list<value_type> ilist){
            clear();
            *this = new SkipList(ilist);
            return *this;
        }

        // iterators
        iterator begin() noexcept{ return iterator(head);}
        const_iterator begin() const noexcept{ return cbegin(); }
        const_iterator cbegin() const{ return const_iterator(head);}
        iterator end() noexcept{
            Node* cur_ptr = head->forward[num_layers];
            while(cur_ptr){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return iterator(cur_ptr);
        }
        const_iterator end() const noexcept{ return cend(); }
        const_iterator cend() const noexcept{
            Node* cur_ptr = head->forward[num_layers];
            while(cur_ptr){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return const_iterator(cur_ptr);
        }
        reverse_iterator rbegin() noexcept{
            Node* cur_ptr = head;
            while(cur_ptr->forward[num_layers]){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return reverse_iterator(cur_ptr);
        }
        const_reverse_iterator rbegin() const noexcept{ return crbegin(); }
        const_reverse_iterator crbegin() const noexcept{
            Node* cur_ptr = head;
            while(cur_ptr->forward[num_layers]){
                cur_ptr = cur_ptr->forward[num_layers];
            }
            return const_reverse_iterator(cur_ptr);
        }
        reverse_iterator rend() noexcept{ return reverse_iterator(head-1); }
        const_reverse_iterator rend() const noexcept{ return crend(); }
        const_reverse_iterator crend() const noexcept{ return const_reverse_iterator(head-1); }

        // capacity
        bool empty() const noexcept{
            return length == 0;
        }
        size_t size() const noexcept{
            return length;
        }
        size_t max_size() const noexcept{
            unsigned int arch_bit = sizeof(void*)*8;
            return std::pow(2, arch_bit)/sizeof(value_type) - 1;
        }

        // modifiers
        void clear() noexcept{
            //TODO don't use erase
            erase(this->begin(), this->end());
        }
        std::pair<iterator, bool> insert(const value_type& value){
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
            if(!cur_ptr || cur_ptr->element < value){
                unsigned int rand_layer = random_level();
                if(rand_layer > num_layers){
                    for(int i = num_layers+1; i < rand_layer+1; ++i){
                        update[i] = head;
                    }
                    num_layers = rand_layer;
                }
                Node* new_node = new Node;
                new_node->element = value;
                for(int i = 0; i <= rand_layer; ++i){
                    new_node->forward[i] = update[i]->forward[i];
                    update[i]->forward[i] = new_node;
                }
                ++length;
                return std::make_pair(iterator(new_node), true);
            }
            return std::make_pair(end(), false);
        }
        std::pair<iterator, bool> insert(value_type&& value){
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
            if(!cur_ptr || cur_ptr->element < value){
                unsigned int rand_layer = random_level();
                if(rand_layer > num_layers){
                    for(int i = num_layers+1; i < rand_layer+1; ++i){
                        update[i] = head;
                    }
                    num_layers = rand_layer;
                }
                Node* new_node = new Node;
                &new_node->element = &value;
                for(int i = 0; i <= rand_layer; ++i){
                    new_node->forward[i] = update[i]->forward[i];
                    update[i]->forward[i] = new_node;
                }
                ++length;
                return std::make_pair(iterator(new_node), true);
            }
            return std::make_pair(end(), false);
        }
        iterator insert(const_iterator pos, const value_type& value){
            Node* cur_ptr = pos.getPtr();
            if(cur_ptr->element > value){
                cur_ptr = head;
            }
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
            if(!cur_ptr || cur_ptr->element < value){
                unsigned int rand_layer = random_level();
                if(rand_layer > num_layers){
                    for(int i = num_layers+1; i < rand_layer+1; ++i){
                        update[i] = head;
                    }
                    num_layers = rand_layer;
                }
                Node* new_node = new Node;
                new_node->element = value;
                for(int i = 0; i <= rand_layer; ++i){
                    new_node->forward[i] = update[i]->forward[i];
                    update[i]->forward[i] = new_node;
                }
                ++length;
                return iterator(new_node);
            }
            return end();
        }
        iterator insert(const_iterator pos, value_type&& value){
            Node* cur_ptr = pos.getPtr();
            if(cur_ptr->element > value){
                cur_ptr = head;
            }
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
            if(!cur_ptr || cur_ptr->element < value){
                unsigned int rand_layer = random_level();
                if(rand_layer > num_layers){
                    for(int i = num_layers+1; i < rand_layer+1; ++i){
                        update[i] = head;
                    }
                    num_layers = rand_layer;
                }
                Node* new_node = new Node;
                &new_node->element = &value;
                for(int i = 0; i <= rand_layer; ++i){
                    new_node->forward[i] = update[i]->forward[i];
                    update[i]->forward[i] = new_node;
                }
                ++length;
                return iterator(new_node);
            }
            return end();
        }
        iterator insert(const_iterator pos, size_t count, const value_type& value){
            for(int i = 0; i < count; ++i){
                insert(pos++, value);
            }
        }
        template <class InputIt>
        void insert(iterator pos, InputIt first, InputIt last){
            auto it = first;
            while(it != last){
                insert(pos++, *it++);
            }
        }
        void insert(std::initializer_list<value_type> ilist){
            auto it = ilist.begin();
            while(it != ilist.end()){
                insert(*it);
                ++it;
            }
        }
        template <class... Args>
        std::pair<iterator, bool> emplace(const_iterator pos, Args&&... args){
            Node* cur_ptr = pos.getPtr();
            if(cur_ptr->element > value_type(std::forward<Args>(args) ...)){
                cur_ptr = head;
            }
            // create an array to store changes on each layer
            Node* update[kMAX_LAYERS+1];
            memset(update, 0, sizeof(Node*)*(kMAX_LAYERS+1));
            //travel down layers and advance cur_ptr until right spot is found
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->forward[i]->element < value_type(std::forward<Args>(args) ...)){
                    cur_ptr = cur_ptr->forward[i];
                }
                update[i] = cur_ptr;
            }
            cur_ptr = cur_ptr->forward[0]; // advance cur_ptr on bottom layer
            if(!cur_ptr || cur_ptr->element < value_type(std::forward<Args>(args) ...)){
                unsigned int rand_layer = random_level();
                if(rand_layer > num_layers){
                    for(int i = num_layers+1; i < rand_layer+1; ++i){
                        update[i] = head;
                    }
                    num_layers = rand_layer;
                }
                Node* new_node = new Node;
                new_node->element = std::move(value_type(std::forward<Args>(args) ...));
                for(int i = 0; i <= rand_layer; ++i){
                    new_node->forward[i] = update[i]->forward[i];
                    update[i]->forward[i] = new_node;
                }
                ++length;
                return std::make_pair(iterator(new_node), true);
            }
            return std::make_pair(this->end(), false);

        }
        template <class... Args>
        iterator emplace(const_iterator pos, Args&&... args){
            return empalce(pos, args...).first;
        }
        size_t erase(const value_type& value){
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
                while(num_layers > 0 && !head->forward[num_layers]){
                    --num_layers;
                }
                --length;
            }
            return length;
        }
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last){
            auto res = this->cend();
            auto it = last;
            while(it != first){
                res = erase(it--);
            }
            return res;
        }
        void swap(SkipList& other){
            if(this != &other) {
                std::swap(this->num_layers, other->num_layers);
                std::swap(this->length, other->length);
                std::swap(this->head, other->head);
            }
        }

        // lookup
        size_t count(const T& value) const{
            auto pair = equal_range(value);
            return std::distance(pair.second - pair.first);
        }
        iterator find(const T& value){
            Node* cur_ptr = head;
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->element < value){
                    if(cur_ptr->element == value)
                        return iterator(cur_ptr);
                    cur_ptr = cur_ptr->forward[i];
                }
            }
            return this->end();
        }
        const_iterator find(const T& value) const{
            const Node* cur_ptr = head;
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->element < value){
                    if(cur_ptr->element == value)
                        return const_iterator(cur_ptr);
                    cur_ptr = cur_ptr->forward[i];
                }
            }
            return this->cend();
        }
        bool contains(const T& value) const{
            return find(value) != this->end();
        }
        std::pair<iterator, iterator> equal_range(const T& value){
            auto start_it = find(value);
            Node* cur_ptr = start_it;
            for(int i = num_layers; i >= 0; --i){
                while(cur_ptr->forward[i] && cur_ptr->element <= value){
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
        void merge(SkipList& other){
            for(T& elem : other){
                insert(elem);
            }
        }
        void merge(SkipList&& other){
            for(T& elem : other){
                insert(std::move(other));
            }
        }
        template <class Comp>
        void merge(SkipList& other, Comp comp);
        template <class Comp>
        void merge(SkipList&& other, Comp comp);
        void remove(const T& value){
            for(auto it = this->begin(); auto last = this->end(); it != last){
                if(*it == value){
                    it = this->erase(it);
                }
                else{
                    ++it;
                }
            }
        }
        template <class UnaryPred>
        void remove_if(UnaryPred p){
            for(auto it = this->begin(); auto last = this->end(); it != last){
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
            return length;
        }
};

template <class T>
bool operator==(const SkipList<T>& lhs, const SkipList<T>& rhs){
    if(lhs.length() != rhs.length()){return false; }
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
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
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