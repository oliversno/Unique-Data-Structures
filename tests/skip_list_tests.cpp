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
    SkipList three{two=one};
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
    two = std::move(one)
    EXPECT_EQ(one, two);
}

TEST(SkipListTests, ilistAssignment){
    SkipList<int> test;
    test = {1,2};
    EXPECT_EQ(test.front(), 1);
    EXPECT_EQ(test.back(), 2);
    EXPECT_EQ(test.size(), 2);
}

TEST(SkipListTests, front){
    SkipList<char> test{'a','b','c'};
    EXPECT_EQ(test.front(), 'a');
}

TEST(SkipListTests, back){
    SkipList<char> test{'a','b','c'};
    EXPECT_EQ(test.back(), 'c');
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