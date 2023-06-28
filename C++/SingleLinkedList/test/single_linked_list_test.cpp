#include <iostream>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "single_linked_list.hpp"

class SingleLinkedListTest : public testing::Test {
 public:
    void SetUp() override {
        slist_int = std::make_shared<SingleLinkedList<int>>();
        slist_str = std::make_shared<SingleLinkedList<std::string>>();

        for (auto in : int_nodes) {
            slist_int->AddNode(in);
            EXPECT_TRUE(slist_int->HasData(in));
        }
        // std::cout << *slist_int << std::endl;

        for (auto sn : str_nodes) {
            slist_str->AddNode(sn);
            EXPECT_TRUE(slist_str->HasData(sn));
        }
        // std::cout << *slist_str << std::endl;

        EXPECT_EQ(slist_int->GetSize(), int_nodes.size());
        EXPECT_EQ(slist_str->GetSize(), str_nodes.size());
    }

    void TearDown() override {
        slist_int.reset();
        slist_str.reset();
    }

 protected:
    std::shared_ptr<SingleLinkedList<int>> slist_int;
    std::shared_ptr<SingleLinkedList<std::string>> slist_str;

    std::vector<int> int_nodes = {7, 8, 9, 10, 14};
    std::vector<std::string> str_nodes = {"seven", "eight", "nine", "ten",
                                          "fourteen"};
};

TEST_F(SingleLinkedListTest, TestDeleteIntData) {
    // Delete 2 end nodes
    slist_int->DeleteNode(10);
    slist_int->DeleteNode(14);
    EXPECT_EQ(slist_int->GetSize(), 3);
}

TEST_F(SingleLinkedListTest, TestCompare2EqualLists) {
    // Delete 2 end nodes
    slist_int->DeleteNode(10);
    slist_int->DeleteNode(14);

    // build a new list with the first 3 nodes
    SingleLinkedList<int> other_list;
    other_list.AddNode(7);
    other_list.AddNode(8);
    other_list.AddNode(9);

    EXPECT_EQ(*slist_int, other_list);
}

TEST_F(SingleLinkedListTest, TestCompare2UnequalLists) {
    SingleLinkedList<int> other_list;
    other_list.AddNode(7);
    other_list.AddNode(8);
    other_list.AddNode(9);

    EXPECT_NE(*slist_int, other_list);
}

TEST_F(SingleLinkedListTest, ReverseList) {
    SingleLinkedList<std::string> reversed_list;
    std::vector<std::string> rev = str_nodes;

    std::reverse(rev.begin(), rev.end());
    for (const auto& r : rev) {
        reversed_list.AddNode(r);
    }

    slist_str->ReverseList();
    EXPECT_EQ(*slist_str, reversed_list);
}

TEST_F(SingleLinkedListTest, TestAddNodeAfterExistingNode) {
    SingleLinkedList<int> other_list;
    other_list.AddNode(7);
    other_list.AddNode(10);
    other_list.AddNode(14);

    other_list.AddNode(7, 8);
    other_list.AddNode(8, 9);

    EXPECT_EQ(*slist_int, other_list);
}

// TODO(emfa): Implement an interator for the list
// TEST_F(SingleLinkedListTest, SwapNodes) {
//     std::vector<std::string> swapped_nodes = {"seven", "ten", "nine", "eight",
//                                               "fourteen"};

//     slist_str->Swap("eight", "ten");

//     EXPECT_EQ(*slist_str, reversed_list);
// }
