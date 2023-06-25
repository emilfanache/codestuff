/*
 *  SortedBinaryTree.cpp
 *
 *  Created on: Mar. 21, 2021
 *      Author: Emil Fanache
 */
#include <algorithm>
#include <iostream>

#include "SortedBinaryTree/SortedBinaryTree.hpp"

SortedBinaryTree::SortedBinaryTree() {
    root = nullptr;
}

SortedBinaryTree::SortedBinaryTree(const SortedBinaryTree& srcTree) {
    root = CopyBinaryTree(srcTree.GetBTreeRoot());
}

Node* SortedBinaryTree::CopyBinaryTree(Node* srcTree) {
    Node* dstTree = nullptr;

    if (!srcTree) {
        return nullptr;
    }

    dstTree = CreateNode(srcTree->_value);
    if (srcTree->_left != nullptr) {
        dstTree->_left = CopyBinaryTree(srcTree->_left);
    }

    if (srcTree->_right != nullptr) {
        dstTree->_right = CopyBinaryTree(srcTree->_right);
    }

    return dstTree;
}

SortedBinaryTree::~SortedBinaryTree() {
    DeleteTree(root);
}

Node* SortedBinaryTree::CreateNode(int value) {
    Node* leaf = new Node;
    leaf->_value = value;
    leaf->_left = nullptr;
    leaf->_right = nullptr;

    return leaf;
}

Node* SortedBinaryTree::AddNode(int value, Node* leaf) {
    if (!root) {
        root = CreateNode(value);
        return root;
    }

    if (!leaf) {
        return nullptr;
    }

    if (value < leaf->_value) {
        if (leaf->_left != nullptr) {
            AddNode(value, leaf->_left);
        } else {
            leaf->_left = CreateNode(value);
        }
    } else {
        if (leaf->_right != nullptr) {
            AddNode(value, leaf->_right);
        } else {
            leaf->_right = CreateNode(value);
        }
    }

    return leaf;
}

Node* SortedBinaryTree::FindNode(int value, Node* leaf) {
    if (!root || !leaf) {
        return nullptr;
    }

    if (value == leaf->_value) {
        return leaf;
    } else if (value < leaf->_value) {
        return FindNode(value, leaf->_left);
    } else {
        return FindNode(value, leaf->_right);
    }
}

void SortedBinaryTree::DeleteTree(Node* leaf) {
    if (!leaf)
        return;

    DeleteTree(leaf->_left);
    DeleteTree(leaf->_right);
    delete leaf;
}

// Left - Root - Right
void SortedBinaryTree::PrintInOrder(Node* leaf) {
    if (!leaf)
        return;

    PrintInOrder(leaf->_left);

    std::cout << leaf->_value << " ";

    PrintInOrder(leaf->_right);
}

// Root - Left - Right
void SortedBinaryTree::PrintPreOrder(Node* leaf) {
    if (!leaf)
        return;

    std::cout << leaf->_value << " ";

    PrintInOrder(leaf->_left);

    PrintInOrder(leaf->_right);
}

// Left - Right - Root
void SortedBinaryTree::PrintPostOrder(Node* leaf) {
    if (!leaf)
        return;

    PrintInOrder(leaf->_left);

    PrintInOrder(leaf->_right);

    std::cout << leaf->_value << " ";
}

void SortedBinaryTree::PrintOneLevel(Node* leaf, int level) {
    if (!leaf || !level) {
        return;
    }

    if (level == 1) {
        std::scout << leaf->_value << " ";
    } else {
        PrintOneLevel(leaf->_left, level - 1);
        PrintOneLevel(leaf->_right, level - 1);
    }
}

void SortedBinaryTree::PrintByLevel(Node* leaf) {
    if (!leaf) {
        return;
    }

    unsigned int maxDepth = GetMaxDepth();
    for (unsigned int i = 1; i <= maxDepth; i++) {
        PrintOneLevel(leaf, i);
        std::cout << std::endl;
    }
}

void SortedBinaryTree::PrintByLevel() {
    PrintByLevel(root);
}

void SortedBinaryTree::PrintBTree(TreePrintOrder order) {
    switch (order) {
        case TPInOrder:
            std::cout << "Print Binary tree method: InOrder" << std::endl;
            PrintInOrder(root);
            break;

        case TPPreOrder:
            std::cout << "Print Binary tree method: PreOrder" << std::endl;
            PrintPreOrder(root);
            break;

        case TPPostOrder:
            std::cout << "Print Binary tree method: PostOrder" << std::endl;
            PrintPostOrder(root);
            break;

        case TPByLevel:
            std::cout << "Print Binary tree method: By Level" << std::endl;
            PrintByLevel();
            break;

        default:
            // set it as default way to iterate through the tree
            PrintInOrder(root);
    }

    std::cout << std::endl << std::endl;
}

// overload method in case there is no param provided
void SortedBinaryTree::PrintBTree() {
    PrintInOrder(root);
    std::cout << std::endl;
}

void SortedBinaryTree::MirrorBTreeHelper(Node* leaf) {
    if (!root || !leaf) {
        return;
    }

    MirrorBTreeHelper(leaf->_left);
    MirrorBTreeHelper(leaf->_right);
    swap(leaf->_left, leaf->_right);
}

void SortedBinaryTree::MirrorBTree() {
    MirrorBTreeHelper(root);
}

Node* SortedBinaryTree::GetBTreeRoot() const {
    return root;
}

bool SortedBinaryTree::TwinTrees(Node* srcTree, Node* dstTree) {
    if (!srcTree && !dstTree) {
        return true;
    } else if (!srcTree || !dstTree) {
        return false;
    }

    if ((srcTree->_value == dstTree->_value) &&
        TwinTrees(srcTree->_left, dstTree->_left) &&
        TwinTrees(srcTree->_right, dstTree->_right)) {
        return true;
    }

    return false;
}

int SortedBinaryTree::MaxDepth(Node* leaf) {
    unsigned int lDepth = 0;
    unsigned int rDepth = 0;

    if (!leaf) {
        return 0;
    }

    if (leaf->_left) {
        lDepth += 1 + MaxDepth(leaf->_left);
    }

    if (leaf->_right) {
        rDepth += 1 + MaxDepth(leaf->_right);
    }

    return (lDepth > rDepth ? lDepth : rDepth);
}

int SortedBinaryTree::GetMaxDepth() {
    return MaxDepth(root);
}

bool IdenticalTrees(SortedBinaryTree& srcTree, SortedBinaryTree& dstTree) {
    Node* srcRoot = srcTree.GetBTreeRoot();
    Node* dstRoot = dstTree.GetBTreeRoot();
    return srcTree.TwinTrees(srcRoot, dstRoot);
}
