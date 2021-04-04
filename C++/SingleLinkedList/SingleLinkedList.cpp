#include <iostream>
#include "SingleLinkedList.hpp"

using namespace std;

template <class T>
SingleLinkedList<T>::SingleLinkedList()
{
    head = nullptr;
    debug = false;
}

template <class T>
SingleLinkedList<T>::SingleLinkedList(bool dbg)
{
    head = nullptr;
    debug = dbg;
}

template <class T>
void SingleLinkedList<T>::AddNode(T data)
{
    Node<T> *n = new Node<T>;
    n->_data = data;
    n->_next = nullptr;

    if (!head)
    {
        head = n;
    }
    else
    {
        Node<T> *current;

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

template <class T>
void SingleLinkedList<T>::AddNode(T dataToFind, T dataToAdd)
{
    if (!head)
    {
        AddNode(dataToAdd);
    }
    else
    {
        Node<T> *current = head;
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
            Node<T> *n = new Node<T>;
            n->_data = dataToAdd;
            n->_next = current->_next;
            current->_next = n;
        }
    }

    return;
}

template <class T>
void SingleLinkedList<T>::DeleteNode(T data)
{
    if (!head)
    {
        return;
    }
    else if (head->_data == data)
    {
        Node<T> *previous = head;
        head = head->_next;
        delete previous;
        return;
    }
    else
    {
        Node<T> *current = head;
        Node<T> *previous;
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

template <class T>
void SingleLinkedList<T>::ReverseList()
{
    Node<T> *current = head;
    Node<T> *previous = nullptr;
    Node<T> *next = nullptr;

    while (current != nullptr)
    {
        next = current->_next;
        current->_next = previous;
        previous = current;
        current = next;
    }

    head = previous;
}

template <class T>
void SingleLinkedList<T>::PrintList(string description)
{
    if (!description.empty())
    {
        cout << "====== " << description.c_str() << " ======" << endl;
    }

    for (Node<T> * current = head; current != nullptr; current = current->_next)
    {
        cout << "[" << current->_data << "]";
        if (current->_next != nullptr)
        {
            cout << " -> ";
        }
    }

    cout << endl;
}

template <class T>
SingleLinkedList<T>::~SingleLinkedList()
{
    Node<T> *next = nullptr;
    Node<T> *current = head;

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

/* !!! Important !!!
 *
 * Added the template class types declarations so I
 * can use the specialized types without including
 * the whole implementation into the header file
 * which is the other way of doing this
 */
template class SingleLinkedList<int>;
template class SingleLinkedList<string>;
