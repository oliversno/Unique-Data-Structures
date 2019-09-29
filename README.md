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

## Bloom Filter
https://en.wikipedia.org/wiki/Bloom_filter
### Description
A Bloom Filter is a space efficient probalistic data structure to test if an element is a member of a set.
False positives are allowed, but false negatives are not. Elements can not be removed once added. A Bloom Filter is an array of m 0 bits
and k hash functions. To add an element the k hash functions are used to find k array positions. Those k bits are set to 1. To test an element the k hash functions are again used to get k positions. If any of those k bits are 0 return negative. If all are 1 return positive.
Bloom filters to do not the elements, a seperate stroage must be used.
### Uses
Bloom Filters can be used to:
* Check if a data item exists localy efore making a server call
* Avoid recomending items to uses if they have already seen them
### Efficiency
|        | Average Case | Worst Case |
|--------|--------------|------------|
| Space  | O(m)         | O(m)       |
| Search | O(k)         | O(k)       |
| Insert |  O(k)        | O(k)       |
| Delete | N/A          | N/A        |
