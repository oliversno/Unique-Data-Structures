#include <gtest/gtest.h>
#include "include/skip_list.h"

TEST(SkipListTests, Init){
    SkipList<int> test;
    SUCCEED();
}

TEST(SkipListTests, InitContaner){
    std::vector<float> vec{0.5, 1.2, 3.14};
    SkipList<float> test{vec.begin(), vec.end()};
    EXPECT_EQ(test.size(), vec.size());
    //TODO check containment
}

TEST(SkipListTests, CopyCtor){
    SkipList<int> one;
    one.insert(4);
    SkipList<int> two{one};
    EXPECT_EQ(one, two);
}

TEST(SkipListTests, MoveCtor){
    SkipList<int> one{5, 7};
    SkipList<int> two;
    SkipList<int> three{two=one};
    EXPECT_EQ(three, one);
}

TEST(SkipListTests, ilistCtor){
    SkipList<std::string> test{"one", "two", "three"};
    EXPECT_EQ(test.size(), 3);
    EXPECT_EQ(test.erase("one"), 2);
    EXPECT_EQ(test.erase("two"), 1);
    EXPECT_EQ(test.erase("three"), 0);
    EXPECT_TRUE(test.empty());
}

TEST(SkipListTests, dtor){
    SkipList<int>* ptr = new SkipList<int>;
    delete ptr;
    SUCCEED();
}

TEST(SkipListTests, assignment){
    SkipList<int> one{};
    one.insert(5);
    SkipList<int> two;
    two = one;
    EXPECT_EQ(one, two);
}

TEST(SkipListTests, moveAssignment){
    SkipList<int> one{5, 7};
    SkipList<int> two;
    two = std::move(one);
    EXPECT_EQ(one, two);
}

TEST(SkipListTests, ilistAssignment){
    SkipList<int> test;
    test = {1,2};
    EXPECT_EQ(*test.cbegin(), 1);
    EXPECT_EQ(*test.cend(), 2);
    EXPECT_EQ(test.size(), 2);
}

TEST(SkipListTests, begin){
    SkipList<char> test{'a','b','c'};
    EXPECT_EQ(*test.begin(), 'a');
}

TEST(SkipListTests, cbegin){
    const SkipList<char> test{'a','b','c'};
    EXPECT_EQ(*test.cbegin(), 'a');
}

TEST(SkipListTests, rbegin){
    SkipList<char> test{'a','b','c'};
    auto it = test.rbegin();
    EXPECT_EQ(*it, 'c');
    ++it;
    EXPECT_EQ(*it, 'b');
}

TEST(SkipListTests, crbegin){
    const SkipList<char> test{'a','b','c'};
    auto it = test.crbegin();
    EXPECT_EQ(*it, 'c');
    ++it;
    EXPECT_EQ(*it, 'b');
}

TEST(SkipListTests, end){
    SkipList<char> test{'a','b','c'};
    EXPECT_EQ(*--test.end(), 'c');
}

TEST(SkipListTests, cend){
    const SkipList<char> test{'a','b','c'};
    EXPECT_EQ(*--test.cend(), 'c');
}

TEST(SkipListTests, rend){
    SkipList<char> test{'a','b','c'};
    auto it = --test.rend();
    EXPECT_EQ(*it, 'a');
    --it;
    EXPECT_EQ(*it, 'b');
}

TEST(SkipListTests, crend){
    const SkipList<char> test{'a','b','c'};
    auto it = --test.crend();
    EXPECT_EQ(*it, 'a');
    --it;
    EXPECT_EQ(*it, 'b');
}

TEST(SkipListTests, empty){
    SkipList<float> test;
    EXPECT_TRUE(test.empty());
    test.insert(1.2);
    EXPECT_FALSE(test.empty());
}

TEST(SkipListTests, size){
    SkipList<float> test;
    EXPECT_EQ(test.size(), 0);
    test.insert(1.2);
    EXPECT_EQ(test.size(), 1);
    test.erase(test.begin());
    EXPECT_EQ(test.size(), 0);
}

//TODO test max_size

TEST(SkipListTests, clear){
    SkipList<std::string> test;
    test = {"cat", "dog", "horse", "chipmunk"};
    EXPECT_FALSE(test.empty());
    test.clear();
    EXPECT_TRUE(test.empty());
}

TEST(SkipListTests, insertValue){
    SkipList<int> test;
    auto pair1 = test.insert(5);
    auto res1 = std::make_pair(test.begin(), true);
    EXPECT_EQ(pair1, res1);
    auto pair2 = test.insert(5);
    auto res2 = std::make_pair(test.end(), false);
    EXPECT_EQ(pair2, res2);
}

TEST(SkipListTests, insertMove){
    SkipList<int> test;
    auto pair1 = test.insert(std::move(5));
    auto res1 = std::make_pair(test.begin(), true);
    EXPECT_EQ(pair1, res1);
    auto pair2 = test.insert(std::move(5));
    auto res2 = std::make_pair(test.end(), false);
    EXPECT_EQ(pair2, res2);
}

TEST(SkipListTests, HinetInsertValue){
    SkipList<int> test;
    auto pair1 = test.insert(test.begin(), 5);
    auto res1 = std::make_pair(test.begin(), true);
    EXPECT_EQ(pair1, res1);
    auto pair2 = test.insert(test.end(), 5);
    auto res2 = std::make_pair(test.end(), false);
    EXPECT_EQ(pair2, res2);
}

TEST(SkipListTests, HintInsertMove){
    SkipList<int> test;
    auto pair1 = test.insert(test.begin(), std::move(5));
    auto res1 = std::make_pair(test.begin(), true);
    EXPECT_EQ(pair1, res1);
    auto pair2 = test.insert(test.end(), std::move(5));
    auto res2 = std::make_pair(test.end(), false);
    EXPECT_EQ(pair2, res2);
}

//TODO test multiple insert

TEST(SkipListTests, insertRange){
    SkipList<int> test;
    std::vector<int> vec = {1,2,3,4,5};
    test.insert(test.end(), vec.begin(), vec.end());
    std::vector<int> res;
    for(int elem : test){
        res.push_back(elem);
    }
    EXPECT_EQ(vec, res);
}

TEST(SkipListTests, insertIList){
    SkipList<int> test;
    std::vector<int> vec = {1,2,3,4,5};
    test.insert({1,2,3,4,5});
    std::vector<int> res;
    for(int elem : test){
        res.push_back(elem);
    }
    EXPECT_EQ(vec, res);
}

TEST(SkipListTests, emplace){
    SkipList<std::vector<char>> test;
    test.emplace(test.begin(), 3, 'c');
    std::vector<char> vec = *test.begin();
    std::vector<char> res = {'c','c','c'};
    EXPECT_EQ(res, vec);
}

TEST(SkipListTests, emplaceConst){
    const SkipList<std::vector<char>> test;
    test.emplace(test.begin(), 3, 'c');
    std::vector<char> vec = *test.cbegin();
    std::vector<char> res = {'c','c','c'};
    EXPECT_EQ(res, vec);
}

TEST(SkipListTests, eraseValue){
    SkipList<int> test;
    test.insert(3);
    EXPECT_EQ(test.size(), 1);
    EXPECT_EQ(*test.begin(), 3);
    size_t new_size = test.erase(36);
    EXPECT_EQ(new_size, 1);
    EXPECT_FALSE(test.empty());
    new_size = test.erase(3);
    EXPECT_EQ(new_size, 0);
    EXPECT_TRUE(test.empty());
}

TEST(SkipListTests, erasePos){
    SkipList<int> test;
    test.insert(3);
    test.insert(40);
    test.erase(test.begin());
    EXPECT_EQ(test.size(), 1);
    EXPECT_EQ(*test.begin(), 3);
}

TEST(SkipListTests, eraseRange){
    SkipList<float> test;
    test.insert(3.14);
    test.insert(1.36);
    test.insert(9.999);
    EXPECT_EQ(test.size(), 3);
    test.erase(test.begin()+1, test.end());
    EXPECT_EQ(test.size(), 1);
    EXPECT_EQ(*test.begin(), 1.36);
}

TEST(SkipListTests, swap){
    SkipList<int> one;
    one = {1,2,3};
    SkipList<int> one_copy{one};
    SkipList<int> two;
    two = {4,5,6};
    SkipList<int> two_copy{two};
    one.swap(two);
    EXPECT_EQ(one, two_copy);
    EXPECT_EQ(two, one_copy);
}

TEST(SkipListTests, count){
    SkipList<char> test;
    test.insert('q');
    test.insert('q');
    test.insert('h');
    EXPECT_EQ(test.count('p'), 1);
    EXPECT_EQ(test.count('q'), 2);
}

TEST(SkipListTests, find){
    SkipList<int> test;
    test.insert(2);
    test.insert(3);
    EXPECT_EQ(test.find(3), test.begin()+1);
}

TEST(SkipListTests, findConst){
    std::vector<int> vec = {2,3};
    SkipList<int> test{vec.begin(), vec.end()};
    EXPECT_EQ(test.find(3), test.cbegin()+1);
}

TEST(SkipListTests, contains){
    SkipList<char> test;
    test.insert('a');
    EXPECT_FALSE(test.contains('c'));
    EXPECT_TRUE(test.contains('a'));
}

TEST(SkipListTests, equal_range){
    SkipList<int> test;
    test.insert(100);
    test.insert(200);
    test.insert(200);
    test.insert(300);
    auto pair = test.equal_range(200);
    EXPECT_EQ(pair.first, test.begin()+1);
    EXPECT_EQ(pair.second, test.end()-1);
}

TEST(SkipListTests, equal_rangeNot){
    SkipList<int> test;
    test.insert(100);
    auto pair = test.equal_range(500);
    EXPECT_EQ(pair.first, test.end());
    EXPECT_EQ(pair.second, test.end());
}
TEST(SkipListTests, equal_rangeConst){
    std::vector<int> vec = {100, 200, 200, 300};
    const SkipList<int> test{vec.begin(), vec.end()};
    auto pair = test.equal_range(200);
    EXPECT_EQ(pair.first, test.begin()+1);
    EXPECT_EQ(pair.second, test.end()-1);
}

TEST(SkipListTests, equal_rangeNotConst){
    std::vector<int> vec = {100};
    const SkipList<int> test{vec.begin(), vec.end()};
    auto pair = test.equal_range(500);
    EXPECT_EQ(pair.first, test.end());
    EXPECT_EQ(pair.second, test.end());
}

TEST(SkipListTests, lower_bound){
    SkipList<float> test;
    test.insert(3.14);
    test.insert(2.0);
    EXPECT_EQ(test.lower_bound(1.5), test.begin());
}

TEST(SkipListTests, upper_bound){
    SkipList<float> test;
    test.insert(5.5);
    test.insert(3.333);
    EXPECT_EQ(test.upper_bound(4), test.begin());
}

TEST(SkipListTests, lower_boundConst){
    std::set<float> set = {3.14, 2.0};
    const SkipList<float> test{set.begin(), set.end()};
    EXPECT_EQ(test.lower_bound(1.5), test.cbegin());
}

TEST(SkipListTests, upper_boundConst){
    std::set<float> set = {5.5, 3.333};
    const SkipList<float> test{set.begin(), set.end()};
    EXPECT_EQ(test.upper_bound(4), test.cbegin());
}

TEST(SkipListTests, merge){
    SkipList<int> one = {1,2,4,5};
    SkipList<int> two = {3,6};
    one.merge(two);
    EXPECT_EQ(one.size(), 6);
}

TEST(SkipListTests, mergeMove){
    SkipList<int> one = {1,2,4,5};
    SkipList<int> two = {3,6};
    one.merge(std::move(two));
    EXPECT_EQ(one.size(), 6);
}

//TODO merge comparator tests

TEST(SkipListTests, remove){
    SkipList<int> test = {60};
    EXPECT_FALSE(test.empty());
    test.remove(60);
    EXPECT_TRUE(test.empty());
}

TEST(SkipListTests, remove_if){
    SkipList<int> test = {1,2,3,4};
    auto is_even = [](int i){ return (i%2 == 0); };
    EXPECT_EQ(test.remove_if(is_even), 2);
}

TEST(SkipListTests, equality){
    SkipList<int> one;
    SkipList<int> two;
    EXPECT_TRUE(one == one);
    EXPECT_TRUE(one == two);
    two.insert(5);
    EXPECT_FALSE(one == two);
}

TEST(SkipListTests, equalityNot){
    SkipList<int> one;
    SkipList<int> two;
    EXPECT_FALSE(one != one);
    EXPECT_FALSE(one != two);
    two.insert(5);
    EXPECT_TRUE(one != two);
}

TEST(SkipListTests, lessThan){
    SkipList<int> one;
    SkipList<int> two = {100};
    EXPECT_FALSE(one < one);
    EXPECT_TRUE(one < two);
    EXPECT_FALSE(two < one);
}

TEST(SkipListTests, Swap){
    SkipList<char> one;
    SkipList<char> two = {'g', 't'};
    swap(one, two);
    EXPECT_TRUE(two.empty());
    EXPECT_FALSE(one.empty());
}