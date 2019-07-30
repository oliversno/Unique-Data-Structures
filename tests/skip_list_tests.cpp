#include <gtest/gtest.h>
#include "include/skip_list.h"

TEST(SkipListTests, Init){
    SkipList<int> test;
    SUCCEED();
}

TEST(SkipListTests, InitCount){
    SkipList<char> test{5, 't'};
    EXPECT_EQ(test.size(), (size_t)5);
    EXPECT_EQ(test.back(), 't');
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

