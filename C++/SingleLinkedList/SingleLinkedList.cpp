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

void SingleLinkedList::AddNode(int data)
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

void SingleLinkedList::AddNode(int dataToFind, int dataToAdd)
{
    if (!head)
    {
        AddNode(dataToAdd);
    }
    else
    {
        Node *current = head;
        bool foundData = false;

        while (current->_next != nullptr)
        {
            if (current->_data == dataToFind)
            {
                foundData = true;
                break;
            }
            current = current->_next;
        }

        if (!foundData || !current->_next)
        {
            if (debug)
            {
                cout << "AddInsideNode fallback: Adding end note" << endl;
            }
            AddNode(dataToAdd);
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
        Node *current = head;
        Node *previous;
        bool foundData = false;

        while (current != nullptr)
        {
            if (current->_data == data)
            {
                foundData = true;
                break;
            }
            previous = current;
            current = current->_next;
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
            cout << " -> ";
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


