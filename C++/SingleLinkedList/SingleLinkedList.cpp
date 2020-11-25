#include <iostream>
#include "SingleLinkedList.hpp"

using namespace std;


SingleLinkedList::SingleLinkedList()
{
  head = nullptr;
  debug = false;
}

SingleLinkedList::SingleLinkedList(bool dbg)
{
  head = nullptr;
  debug = dbg;
}

void SingleLinkedList::AddEndNode(int data)
{
  Node *n = new Node;
  n->_data = data;
  n->_next = nullptr;

  if (!head)
  {
    head = n;
  }
  else
  {
    Node *current;

    // this should take me to the end of the list
    for (current = head; current->_next != nullptr; current = current->_next);
    if (debug)
    {
      cout << "I'm at: [" << current->_data << "], adding node:"<< n->_data << endl;
    }
    current->_next = n;
  }

  return;
}

void SingleLinkedList::AddInsideNode(int dataToFind, int dataToAdd)
{
  if (!head)
  {
    AddEndNode(dataToAdd);
  }
  else
  {
    Node *current;
    bool foundData = false;

    for (current = head; current->_next != nullptr; current = current->_next)
    {
      if (current->_data == dataToFind)
      {
        foundData = true;
        break;
      }
    }

    if (!foundData || !current->_next)
    {
      if (debug)
      {
        cout << "AddInsideNode fallback: Adding end note" << endl;
      }
      AddEndNode(dataToAdd);
    }
    else
    {
      Node *n = new Node;
      n->_data = dataToAdd;
      n->_next = current->_next;
      current->_next = n;
    }
  }

 return;
}

void SingleLinkedList::DeleteNode(int data)
{
  if (!head)
  {
    return;
  }
  else if (head->_data == data)
  {
    Node *previous = head;
    head = head->_next;
    delete previous;
    return;
  }
  else
  {
    Node *current;
    Node *previous;
    bool foundData = false;
    for (current = head; current->_next != nullptr; current = current->_next)
    {
      if (current->_data == data)
      {
        foundData = true;
        break;
      }
      previous = current;
    }

    if (foundData)
    {
      previous->_next = current->_next;
      delete current;
    }
  }

  return;
}

void SingleLinkedList::ReverseList()
{
  Node *current = head;
  Node *previous = nullptr;
  Node *next = nullptr;

  while (current != nullptr)
  {
    next = current->_next;
    current->_next = previous;
    previous = current;
    current = next;
  }

  head = previous;
}

void SingleLinkedList::PrintList(string description)
{
  if (!description.empty())
  {
    cout << "====== " << description.c_str() << " ======" << endl;
  }

  for (Node * current = head; current != nullptr; current = current->_next)
  {
    cout << "[" << current->_data << "]";
    if (current->_next != nullptr)
    {
      cout << "->";
    }
  }

  cout << endl;
}

SingleLinkedList::~SingleLinkedList()
{
  Node *next = nullptr;
  Node *current = head;

  while (current != nullptr)
  {
    next = current->_next;
    if (debug)
    {
      cout << "Destroying node with data:" << current->_data << endl;
    }
    delete current;
    current = next;
  }

  head = nullptr;
}


