/*
 *  SortedBinaryTree.hpp
 *
 *  Created on: Mar. 21, 2021
 *      Author: Emil Fanache
 */
#include <iostream>
#include <memory>

#include "SortedBinaryTree/SortedBinaryTree.hpp"

int main() {
    Node* leaf = nullptr;
    SortedBinaryTree bTree;

    // create root node
    leaf = bTree.AddNode(5, nullptr);
    leaf = bTree.AddNode(12, leaf);
    leaf = bTree.AddNode(7, leaf);
    leaf = bTree.AddNode(9, leaf);
    leaf = bTree.AddNode(15, leaf);
    leaf = bTree.AddNode(3, leaf);
    leaf = bTree.AddNode(16, leaf);
    leaf = bTree.AddNode(22, leaf);
    leaf = bTree.AddNode(11, leaf);
    leaf = bTree.AddNode(6, leaf);

    std::cout << "Max Depth: " << bTree.GetMaxDepth() << std::endl;

    std::cout << "=====   Print binary trees:   =====" << std::endl;
    bTree.PrintBTree(TPInOrder);
    bTree.PrintBTree(TPPreOrder);
    bTree.PrintBTree(TPPostOrder);
    bTree.PrintBTree(TPByLevel);

    std::cout << "=====   Mirror binary tree:   =====" << std::endl;
    SortedBinaryTree copyBeforeMirror = bTree;
    bTree.PrintBTree(TPInOrder);
    bTree.MirrorBTree();
    bTree.PrintBTree(TPInOrder);

    std::cout << "=====   Copy binary tree:   =====" << std::endl;
    SortedBinaryTree copyTree = bTree;

    copyTree.PrintBTree(TPInOrder);

    std::cout
        << "=====   Compare Mirrored Tree and the Copy of the Mirror:   ====="
        << std::endl;
    if (IdenticalTrees(bTree, copyTree)) {
        std::cout << "=====  The Trees are Identical   =====" << std::endl;
    } else {
        std::cout << "=====  The Trees are Different   =====" << std::endl;
    }

    std::cout << "=====   Compare Initial Tree and the Mirrored Copy:   ====="
              << std::endl;
    if (IdenticalTrees(bTree, copyBeforeMirror)) {
        std::cout << "=====  The Trees are Identical   =====" << std::endl;
    } else {
        std::cout << "=====  The Trees are Different   =====" << std::endl;
    }

    return 0;
}
