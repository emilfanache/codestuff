/*
 * SingleLinkedList.hpp
 *
 *  Created on: Nov. 7, 2020
 *      Author: Emil Fanache
 */

#ifndef SINGLELINKEDLIST_HPP_
#define SINGLELINKEDLIST_HPP_

#include <string>

using namespace std;

template <typename T>
struct Node
{
    Node*   _next;
    T       _data;
};

template <class T>
class SingleLinkedList
{
private:
    Node<T>* head;
    bool debug;

public:
    SingleLinkedList();
    SingleLinkedList(bool dbg);
    ~SingleLinkedList();
    void PrintList(string description);
    void ReverseList();
    void AddNode(T data);
    void AddNode(T dataToFind, T dataToAdd);
    void DeleteNode(T data);
};


#endif /* SINGLELINKEDLIST_HPP_ */
