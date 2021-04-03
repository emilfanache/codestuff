/*
 *  SortedBinaryTree.hpp
 *
 *  Created on: Mar. 21, 2021
 *      Author: Emil Fanache
 */

#ifndef SORTEDBINARYTREE_HPP_
#define SORTEDBINARYTREE_HPP_

enum TreePrintOrder
{
    TPInOrder,
    TPPreOrder,
    TPPostOrder
};

struct Node
{
  int _value;
  Node *_left;
  Node *_right;
};

class  SortedBinaryTree
{
  private:
    Node* root;

    Node* CreateNode(int value);
    void DeleteTree(Node *leaf);
    void PrintInOrder(Node *leaf);
    void PrintPreOrder(Node *leaf);
    void PrintPostOrder(Node *leaf);
    void MirrorBTreeHelper(Node *leaf);
    Node* CopyBinaryTree(Node *srcTree);
    Node* GetBTreeRoot() const;
    bool TwinTrees(Node *srcTree, Node *dstTree);

  public:
    SortedBinaryTree();
    SortedBinaryTree(const SortedBinaryTree& dstTree);
    ~ SortedBinaryTree();
    Node* AddNode(int value, Node *leaf);
    Node* FindNode(int value, Node *leaf);
    void PrintBTree(TreePrintOrder order);
    void PrintBTree();
    void MirrorBTree();
    friend bool IdenticalTrees(SortedBinaryTree &, SortedBinaryTree &);

};

#endif /* SORTEDBINARYTREE_HPP_ */
