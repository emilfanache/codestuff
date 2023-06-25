/*
 * HashTable.hpp
 *
 *  Created on: Nov. 17, 2020
 *      Author: Emil Fanache
 */

#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include "iostream"

struct Node {
    Node* _next;
    string _name;
};

const unsigned long numberOfBuckets = 20;

class HashTable {
   private:
    Node* hTable[numberOfBuckets];

   public:
    HashTable();
    ~HashTable();
    unsigned long Hash(string key);
    void AddName(string name);
    bool HasName(string name);
    void DeleteName(string name);
    void DeleteBucket(unsigned long bucketIdx);
    void DisplayBucket(unsigned long bucketIdx);
    void DisplayAll();
};

#endif /* HASHTABLE_HPP_ */
