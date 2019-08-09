# Implementations of Unique Data Structures in C++
## Skip List
https://en.wikipedia.org/wiki/Skip_list
### Description
A Skip List stores an ordered sequence of elements. The elements need not be unique. A Skip List is made of a hieracrchy of linked list layers. The bottom layer is a complete linked list and each additional layer acts as an express lane to acsess elements. Thus the Skip List can be searched quickly but maintains the insertion and deletion speed bennifits of a linked list.
### Uses
Skip Lists can be used to:
* Efficiently calculate running medians
* Represent distributed systems (where Nodes represent Computers and Pointers represent network connections)
* Impliment lockless concurrent priority queues
### Efficiency
|        | Average Case | Worst Case |
|--------|--------------|------------|
| Space  | O(n)         | O(nlogn)   |
| Search | O(logn)      | O(n)       |
| Insert |  O(logn)     | O(n)       |
| Delete | O(logn)      | O(n)       |
