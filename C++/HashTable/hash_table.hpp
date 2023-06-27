/*
 * hash_table.hpp
 *
 *  Created on: Nov. 17, 2020
 *      Author: Emil Fanache
 */

#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <iostream>
#include <string>

struct Node {
    Node* next_;
    std::string name_;
};

const uint32_t kNumberOfBuckets = 20;

class HashTable {
 public:
    HashTable();
    ~HashTable();
    void AddName(const std::string& name);
    bool HasName(const std::string& name);
    void DeleteName(const std::string& name);

    // acceses GetBucket() which is private
    friend std::ostream& operator<<(std::ostream& out, const HashTable& table);

 private:
    uint32_t Hash(const std::string& key);
    Node* GetBucket(uint32_t bucketIdx) const;
    void DeleteBucket(uint32_t bucketIdx);

    Node* h_table[kNumberOfBuckets];
};

std::ostream& operator<<(std::ostream& out, const HashTable& table);

#endif  // HASHTABLE_HPP_
