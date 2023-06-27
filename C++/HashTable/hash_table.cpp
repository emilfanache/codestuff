/*
 * hash_table.cpp
 *
 *  Created on: Nov. 17, 2020
 *      Author: Emil Fanache
 */

#include <iostream>

#include "hash_table.hpp"

HashTable::HashTable() {
    for (auto i = 0; i < kNumberOfBuckets; i++) {
        h_table[i] = nullptr;
    }
}

// djb2 algorithm by Dan Bernstein
uint32_t HashTable::Hash(const std::string& key) {
    uint32_t hash = 5381;
    for (uint32_t i = 0; i < key.size(); i++) {
        hash = (hash << 5) + hash + key[i]; /* hash * 33 + c */
    }

    return (hash % kNumberOfBuckets);
}

void HashTable::AddName(const std::string& name) {
    if (HasName(name)) {
        return;
    }

    uint32_t hIndex = Hash(name);

    if (!h_table[hIndex]) {
        h_table[hIndex] = new Node;
        h_table[hIndex]->name_ = name;
        h_table[hIndex]->next_ = nullptr;
    } else {
        Node* bucket_head = h_table[hIndex];
        Node* person = new Node;
        person->name_ = name;
        person->next_ = nullptr;

        // go to the end of the current bucket chain
        // so we can add the new person in the list
        while (bucket_head->next_ != nullptr) {
            bucket_head = bucket_head->next_;
        }
        bucket_head->next_ = person;
    }
}

bool HashTable::HasName(const std::string& name) {
    uint32_t hIndex = Hash(name);

    if (!h_table[hIndex]) {
        return false;
    } else {
        Node* bucket_head = h_table[hIndex];
        while (bucket_head != nullptr) {
            if (bucket_head->name_ == name) {
                return true;
            }
            bucket_head = bucket_head->next_;
        }
    }
    return false;
}

void HashTable::DeleteName(const std::string& name) {
    uint32_t hIndex = Hash(name);

    if (!h_table[hIndex]) {
        return;
    } else if (h_table[hIndex]->name_ == name) {
        // head node hold the name I am looking for
        Node* previousNode = h_table[hIndex];
        h_table[hIndex] = h_table[hIndex]->next_;
        delete previousNode;
    } else {
        Node* bucket_head = h_table[hIndex];
        Node* previousNode = nullptr;
        bool foundName = false;

        while (bucket_head != nullptr) {
            if (bucket_head->name_ == name) {
                foundName = true;
                break;
            }
            previousNode = bucket_head;
            bucket_head = bucket_head->next_;
        }

        if (foundName) {
            previousNode->next_ = bucket_head->next_;
            delete bucket_head;
            return;
        }
    }
}

Node* HashTable::GetBucket(uint32_t bucketIdx) const {
    if (!h_table[bucketIdx]) {
        return nullptr;
    }

    return h_table[bucketIdx];
}

void HashTable::DeleteBucket(uint32_t bucketIdx) {
    Node* bucket_head = h_table[bucketIdx];
    Node* prevNode = nullptr;

    if (!bucket_head)
        return;

    while (bucket_head != nullptr) {
        prevNode = bucket_head;
        bucket_head = bucket_head->next_;
        if (prevNode) {
            delete prevNode;
        }
    }
}

HashTable::~HashTable() {
    for (uint32_t i = 0; i < kNumberOfBuckets; i++) {
        if (h_table[i]) {
            DeleteBucket(i);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const HashTable& table) {
    for (uint32_t idx = 0; idx < kNumberOfBuckets; idx++) {
        Node* bucket = table.GetBucket(idx);
        if (!bucket)
            continue;

        Node* bucket_head = bucket;

        if (bucket_head != nullptr) {
            out << "IDX:" << idx << " ";
        }

        while (bucket_head != nullptr) {
            out << "[" << bucket_head->name_ << "]";
            if (bucket_head->next_ != nullptr) {
                out << "->";
            }
            bucket_head = bucket_head->next_;
        }
        out << std::endl;
    }

    return out;
}
