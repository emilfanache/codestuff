#include <iostream>
#include <string>

#include "single_linked_list.hpp"

template <class T>
SingleLinkedList<T>::SingleLinkedList() {
    head_ = nullptr;
    debug_ = false;
}

template <class T>
SingleLinkedList<T>::SingleLinkedList(bool dbg) {
    head_ = nullptr;
    debug_ = dbg;
}

template <class T>
void SingleLinkedList<T>::AddNode(T data) {
    Node<T>* n = new Node<T>;
    n->data_ = data;
    n->next_ = nullptr;

    if (!head_) {
        head_ = n;
    } else {
        Node<T>* current = head_;
        while (current->next_ != nullptr) {
            current = current->next_;
        }

        // this should take me to the end of the list
        if (debug_) {
            std::cout << "I'm at: [" << current->data_
                      << "], adding node:" << n->data_ << std::endl;
        }
        current->next_ = n;
    }

    return;
}

template <class T>
void SingleLinkedList<T>::AddNode(T dataToFind, T dataToAdd) {
    if (!head_) {
        AddNode(dataToAdd);
    } else {
        Node<T>* current = head_;
        bool foundData = false;

        while (current->next_ != nullptr) {
            if (current->data_ == dataToFind) {
                foundData = true;
                break;
            }
            current = current->next_;
        }

        if (!foundData || !current->next_) {
            if (debug_) {
                std::cout << "AddInsideNode fallback: Adding end note"
                          << std::endl;
            }
            AddNode(dataToAdd);
        } else {
            Node<T>* n = new Node<T>;
            n->data_ = dataToAdd;
            n->next_ = current->next_;
            current->next_ = n;
        }
    }

    return;
}

template <class T>
void SingleLinkedList<T>::DeleteNode(T data) {
    if (!head_) {
        return;
    } else if (head_->data_ == data) {
        Node<T>* previous = head_;
        head_ = head_->next_;
        delete previous;
        return;
    } else {
        Node<T>* current = head_;
        Node<T>* previous;
        bool foundData = false;

        while (current != nullptr) {
            if (current->data_ == data) {
                foundData = true;
                break;
            }
            previous = current;
            current = current->next_;
        }

        if (foundData) {
            previous->next_ = current->next_;
            delete current;
        }
    }

    return;
}

template <class T>
void SingleLinkedList<T>::ReverseList() {
    Node<T>* current = head_;
    Node<T>* previous = nullptr;
    Node<T>* next = nullptr;

    while (current != nullptr) {
        next = current->next_;
        current->next_ = previous;
        previous = current;
        current = next;
    }

    head_ = previous;
}

template <class T>
void SingleLinkedList<T>::SwapNodes(Node<T>** firstNode, Node<T>** secondNode) {
    Node<T>* localNode = *firstNode;
    *firstNode = *secondNode;
    *secondNode = localNode;
}

template <class T>
void SingleLinkedList<T>::Swap(T first, T second) {
    Node<T>* current = head_;
    Node<T>* previous = nullptr;
    Node<T>* firstNode = nullptr;
    Node<T>* previousFirst = nullptr;
    Node<T>* secondNode = nullptr;
    Node<T>* previousSecond = nullptr;

    while (current != nullptr) {
        if (current->data_ == first) {
            firstNode = current;
            previousFirst = previous;
        } else if (current->data_ == second) {
            secondNode = current;
            previousSecond = previous;
        }

        // if we found both nodes no need to iterate further
        if (firstNode && secondNode)
            break;

        previous = current;
        current = current->next_;
    }

    if (!firstNode || !secondNode)
        return;

    if (previousFirst != nullptr) {
        previousFirst->next_ = secondNode;
    } else {
        head_ = secondNode;
    }

    if (previousSecond != nullptr) {
        previousSecond->next_ = firstNode;
    } else {
        head_ = firstNode;
    }

    SwapNodes(&firstNode->next_, &secondNode->next_);
}

template <class T>
uint32_t SingleLinkedList<T>::GetSize() const {
    uint32_t size = 0;

    Node<T>* current = head_;
    while (current != nullptr) {
        size++;
        current = current->next_;
    }

    return size;
}

template <class T>
bool SingleLinkedList<T>::HasData(T data) {
    Node<T>* current = head_;
    while (current != nullptr) {
        if (current->data_ == data) {
            return true;
        }
        current = current->next_;
    }

    return false;
}

template <class T>
SingleLinkedList<T>::~SingleLinkedList() {
    Node<T>* next = nullptr;
    Node<T>* current = head_;

    while (current != nullptr) {
        next = current->next_;
        if (debug_) {
            std::cout << "Destroying node with data:" << current->data_
                      << std::endl;
        }
        delete current;
        current = next;
    }

    head_ = nullptr;
}

/* !!! Important !!!
 *
 * Added the template class types declarations so I
 * can use the specialized types without including
 * the whole implementation into the head_er file
 * which is the other way of doing this
 */
template class SingleLinkedList<int>;
template class SingleLinkedList<std::string>;
