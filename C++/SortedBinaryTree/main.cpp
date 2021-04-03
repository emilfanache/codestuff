/*
 *  SortedBinaryTree.hpp
 *
 *  Created on: Mar. 21, 2021
 *      Author: Emil Fanache
 */
#include <iostream>
#include <memory>

#include "SortedBinaryTree.hpp"

using namespace std;


int main()
{
    Node* leaf = nullptr;
    SortedBinaryTree bTree;

    // create root node
    leaf =  bTree.AddNode(5, nullptr);
    leaf =  bTree.AddNode(12, leaf);
    leaf =  bTree.AddNode(7, leaf);
    leaf =  bTree.AddNode(9, leaf);
    leaf =  bTree.AddNode(15, leaf);
    leaf =  bTree.AddNode(3, leaf);
    leaf =  bTree.AddNode(16, leaf);
    leaf =  bTree.AddNode(22, leaf);
    leaf =  bTree.AddNode(11, leaf);
    leaf =  bTree.AddNode(6, leaf);

    cout << "=====   Print binary trees:   =====" << endl;
    bTree.PrintBTree(TPInOrder);
    bTree.PrintBTree(TPPreOrder);
    bTree.PrintBTree(TPPostOrder);

    cout << "=====   Mirror binary tree:   =====" << endl;
    SortedBinaryTree copyBeforeMirror = bTree;
    bTree.PrintBTree(TPInOrder);
    bTree.MirrorBTree();
    bTree.PrintBTree(TPInOrder);

    cout << "=====   Copy binary tree:   =====" << endl;
    SortedBinaryTree copyTree = bTree;

    copyTree.PrintBTree(TPInOrder);

    cout << "=====   Compare Mirrored Tree and the Copy of the Mirror:   =====" << endl;
    if (IdenticalTrees(bTree, copyTree))
    {
        cout << "=====  The Trees are Identical   =====" << endl;
    }
    else
    {
        cout << "=====  The Trees are Different   =====" << endl;
    }

    cout << "=====   Compare Initial Tree and the Mirrored Copy:   =====" << endl;
    if (IdenticalTrees(bTree, copyBeforeMirror))
    {
        cout << "=====  The Trees are Identical   =====" << endl;
    }
    else
    {
        cout << "=====  The Trees are Different   =====" << endl;
    }
    return 0;
}
