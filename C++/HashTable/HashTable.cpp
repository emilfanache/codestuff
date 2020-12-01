/*
 * HashTable.cpp
 *
 *  Created on: Nov. 17, 2020
 *      Author: Emil Fanache
 */

#include "HashTable.hpp"

using namespace std;

HashTable::HashTable()
{
    for (unsigned long i = 0; i < numberOfBuckets; i++)
    {
        hTable[i] = nullptr;
    }
}

// djb2 algorithm by Dan Bernstein
unsigned long HashTable::Hash(string key)
{
    unsigned long hash = 5381;
    for (unsigned int i = 0; i < key.size(); i++)
    {
        hash = (hash << 5) + hash + key[i]; /* hash * 33 + c */
    }

    return (hash % numberOfBuckets);
}

void HashTable::AddName(string name)
{
    unsigned long hIndex = Hash(name);

    if (!hTable[hIndex])
    {
        hTable[hIndex] = new Node;
        hTable[hIndex]->_name = name;
        hTable[hIndex]->_next = nullptr;
    }
    else
    {
        Node *bucketHead = hTable[hIndex];
        Node *person = new Node;
        person->_name = name;
        person->_next = nullptr;

        // go to the end of the current bucket chain
        // so we can add the new person in the list
        while (bucketHead->_next != nullptr)
        {
            bucketHead = bucketHead->_next;
        }
        bucketHead->_next = person;
    }
}

bool HashTable::HasName(string name)
{
    unsigned long hIndex = Hash(name);

    if (!hTable[hIndex])
    {
        return false;
    }
    else
    {
        Node *bucketHead = hTable[hIndex];
        while (bucketHead != nullptr)
        {
            if (bucketHead->_name == name)
            {
                return true;
            }
            bucketHead = bucketHead->_next;
        }
    }
    return false;
}

void HashTable::DeleteName(string name)
{
    unsigned long hIndex = Hash(name);

    if (!hTable[hIndex])
    {
        return;
    }
    else if (hTable[hIndex]->_name == name)
    {
        // head node hold the name I am looking for
        Node *previousNode = hTable[hIndex];
        hTable[hIndex] =  hTable[hIndex]->_next;
        delete previousNode;
    }
    else
    {
        Node *bucketHead = hTable[hIndex];
        Node *previousNode = nullptr;
        bool foundName = false;

        while (bucketHead != nullptr)
        {
            if (bucketHead->_name == name)
            {
                foundName = true;
                break;
            }
            previousNode = bucketHead;
            bucketHead = bucketHead->_next;
        }

        if (foundName)
        {
            previousNode->_next = bucketHead->_next;
            delete bucketHead;
            return;
        }
    }
}

void HashTable::DeleteBucket(unsigned long bucketIdx)
{
    Node *bucketHead = hTable[bucketIdx];
    Node *prevNode = nullptr;
    if (!bucketHead)
        return;

    while (bucketHead != nullptr)
    {
      prevNode = bucketHead;
      bucketHead = bucketHead->_next;
      if (prevNode)
      {
          delete prevNode;
      }
    }
}

void HashTable::DisplayBucket(unsigned long bucketIdx)
{
    Node *bucketHead = hTable[bucketIdx];

    if (bucketHead != nullptr)
    {
        cout << "IDX:" << bucketIdx << " ";
    }

    while (bucketHead != nullptr)
    {
      cout << "[" << bucketHead->_name << "]";
      if (bucketHead->_next != nullptr)
      {
        cout << "->";
      }
      bucketHead = bucketHead->_next;
    }
    cout << endl;
}

void HashTable::DisplayAll()
{
    for (unsigned long i = 0; i < numberOfBuckets; i++)
    {
        if (!hTable[i])
            continue;

        DisplayBucket(i);
    }
}

HashTable::~HashTable()
{
    for (unsigned long i = 0; i < numberOfBuckets; i++)
    {
        if (hTable[i])
        {
            DeleteBucket(i);
        }
    }
}

