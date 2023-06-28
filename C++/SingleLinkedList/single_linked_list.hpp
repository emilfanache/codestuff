/*
 * single_linked_list.hpp
 *
 *  Created on: Nov. 7, 2020
 *      Author: Emil Fanache
 */

#ifndef SINGLE_LINKED_LIST_HPP_
#define SINGLE_LINKED_LIST_HPP_

#include <string>

template <typename T>
struct Node {
    Node* next_;
    T data_;
};

template <class T>
class SingleLinkedList {
 public:
    SingleLinkedList();
    explicit SingleLinkedList(bool dbg);
    ~SingleLinkedList();
    void ReverseList();
    void AddNode(T data);
    void AddNode(T dataToFind, T dataToAdd);
    void Swap(T first, T second);
    void DeleteNode(T data);
    uint32_t GetSize() const;
    bool HasData(T data);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out,
                                    const SingleLinkedList<U>& slist);
    template <typename U>
    friend bool operator==(const SingleLinkedList<U>& lhs,
                           const SingleLinkedList<U>& rhs);
    template <typename U>
    friend bool operator!=(const SingleLinkedList<U>& lhs,
                           const SingleLinkedList<U>& rhs);

 private:
    void SwapNodes(Node<T>** firstNode, Node<T>** secondNode);

    Node<T>* head_;
    bool debug_;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SingleLinkedList<T>& slist) {
    Node<T>* current = slist.head_;
    while (current != nullptr) {
        out << "[" << current->data_ << "]";
        if (current->next_ != nullptr) {
            out << " -> ";
        }

        current = current->next_;
    }
    out << std::endl;
    return out;
}

template <class T>
bool operator==(const SingleLinkedList<T>& lhs,
                const SingleLinkedList<T>& rhs) {
    Node<T>* lhs_current = lhs.head_;
    Node<T>* rhs_current = rhs.head_;

    if (lhs_current == nullptr && rhs_current == nullptr) {
        return true;
    }

    if (lhs.GetSize() != rhs.GetSize()) {
        return false;
    }

    while (lhs_current != nullptr && rhs_current != nullptr) {
        if (lhs_current->data_ != rhs_current->data_) {
            return false;
        }
        lhs_current = lhs_current->next_;
        rhs_current = rhs_current->next_;
    }

    return true;
}

template <class T>
bool operator!=(const SingleLinkedList<T>& lhs,
                const SingleLinkedList<T>& rhs) {
    return !operator==(lhs, rhs);
}
#endif  // SINGLE_LINKED_LIST_HPP
