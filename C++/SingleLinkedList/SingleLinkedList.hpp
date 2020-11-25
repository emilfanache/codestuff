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

typedef struct Node_t
{
  Node_t*   _next;
  int       _data;
} Node;


class SingleLinkedList
{
private:
  Node* head;
  bool debug;

public:
  SingleLinkedList();
  SingleLinkedList(bool dbg);
  ~SingleLinkedList();
  void PrintList(string description);
  void ReverseList();
  void AddEndNode(int data);
  void AddInsideNode(int dataToFind, int dataToAdd);
  void DeleteNode(int data);
};


#endif /* SINGLELINKEDLIST_HPP_ */
