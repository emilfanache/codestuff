#include <iostream>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "hash_table.hpp"

class HashTableTesting : public testing::Test {
 public:
    void SetUp() override {
        ht = std::make_shared<HashTable>();
        for (const auto& nm : names) {
            ht->AddName(nm);
            EXPECT_TRUE(ht->HasName(nm));
        }

        // std::cout << *ht << std::endl;
    }
    void TearDown() override { ht.reset(); }

 protected:
    std::shared_ptr<HashTable> ht;
    std::vector<std::string> names = {
        "Sam",       "Cook",      "John",       "Sandra",   "Maria",
        "Georgescu", "Lucian",    "Grigorescu", "Eminescu", "Bacovia",
        "Cosbuc",    "Minulescu", "Goga",       "Dorian",   "Napoleon",
        "Richard",   "Charles",   "Ludovic",    "Henry",    "George"};
};

TEST_F(HashTableTesting, TestDeleteName) {
    std::string del_name = "Sandra";
    ht->DeleteName(del_name);
    EXPECT_FALSE(ht->HasName(del_name));
}
