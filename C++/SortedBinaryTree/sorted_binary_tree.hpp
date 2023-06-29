/*
 *  sorted_binary_tree.hpp
 *
 *  Created on: Mar. 21, 2021
 *      Author: Emil Fanache
 */

#ifndef SORTED_BINARY_TREE_HPP_
#define SORTED_BINARY_TREE_HPP_

enum TreePrintOrder { TPInOrder, TPPreOrder, TPPostOrder, TPByLevel };

struct Node {
    int _value;
    Node* _left;
    Node* _right;
};

class SortedBinaryTree {
 private:
    Node* root;

    Node* CreateNode(int value);
    void DeleteTree(Node* leaf);
    void PrintInOrder(Node* leaf);
    void PrintPreOrder(Node* leaf);
    void PrintPostOrder(Node* leaf);
    void PrintByLevel(Node* leaf, int level);
    int MaxDepth(Node* leaf);
    void MirrorBTreeHelper(Node* leaf);
    Node* CopyBinaryTree(Node* srcTree);
    Node* GetBTreeRoot() const;
    bool TwinTrees(Node* srcTree, Node* dstTree);
    void PrintByLevel(Node* leaf);
    void PrintOneLevel(Node* leaf, int level);

 public:
    SortedBinaryTree();
    SortedBinaryTree(const SortedBinaryTree& dstTree);
    ~SortedBinaryTree();
    Node* AddNode(int value, Node* leaf);
    Node* FindNode(int value, Node* leaf);
    void PrintBTree(TreePrintOrder order);
    void PrintBTree();
    void MirrorBTree();
    int GetMaxDepth();
    void PrintByLevel();
    friend bool IdenticalTrees(const SortedBinaryTree&,
                               const SortedBinaryTree&);
};

#endif  // SORTED_BINARY_TREE_HPP_
