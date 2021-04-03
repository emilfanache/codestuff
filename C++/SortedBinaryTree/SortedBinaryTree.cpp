/*
 *  SortedBinaryTree.cpp
 *
 *  Created on: Mar. 21, 2021
 *      Author: Emil Fanache
 */

#include "SortedBinaryTree.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

SortedBinaryTree::SortedBinaryTree()
{
    root = nullptr;
}

SortedBinaryTree::SortedBinaryTree(const SortedBinaryTree& srcTree)
{
    root = CopyBinaryTree(srcTree.GetBTreeRoot());
}

Node *SortedBinaryTree::CopyBinaryTree(Node *srcTree)
{
    Node *dstTree = nullptr;

    if (!srcTree)
    {
        return nullptr;
    }

    dstTree = CreateNode(srcTree->_value);
    if (srcTree->_left != nullptr)
    {
        dstTree->_left = CopyBinaryTree(srcTree->_left);
    }

    if (srcTree->_right != nullptr)
    {
        dstTree->_right = CopyBinaryTree(srcTree->_right);
    }

    return dstTree;
}

SortedBinaryTree::~ SortedBinaryTree()
{
    DeleteTree(root);
}

Node * SortedBinaryTree::CreateNode(int value)
{
    Node *leaf = new Node;
    leaf->_value = value;
    leaf->_left = nullptr;
    leaf->_right = nullptr;

    return leaf;
}

Node* SortedBinaryTree::AddNode(int value, Node *leaf)
{
    if (!root)
    {
        root = CreateNode(value);
        return root;
    }

    if (!leaf)
    {
        return nullptr;
    }

    if (value < leaf->_value)
    {
        if (leaf->_left != nullptr)
        {
            AddNode(value, leaf->_left);
        }
        else
        {
            leaf->_left = CreateNode(value);
        }
    }
    else
    {
        if (leaf->_right != nullptr)
        {
            AddNode(value, leaf->_right);
        }
        else
        {
            leaf->_right = CreateNode(value);
        }
    }

    return leaf;
}

Node*  SortedBinaryTree::FindNode(int value, Node *leaf)
{
    if (!root || !leaf)
    {
        return nullptr;
    }

    if (value == leaf->_value)
    {
        return leaf;
    }
    else if (value < leaf->_value)
    {
        return FindNode(value, leaf->_left);
    }
    else
    {
        return FindNode(value, leaf->_right);
    }
}

void  SortedBinaryTree::DeleteTree(Node *leaf)
{
    if (!leaf)
        return;

    DeleteTree(leaf->_left);
    DeleteTree(leaf->_right);
    delete leaf;
}

// Left - Root - Right
void  SortedBinaryTree::PrintInOrder(Node *leaf)
{
    if (!leaf)
        return;

    PrintInOrder(leaf->_left);

    cout << leaf->_value << " ";

    PrintInOrder(leaf->_right);
}

// Root - Left - Right
void  SortedBinaryTree::PrintPreOrder(Node *leaf)
{
    if (!leaf)
        return;

    cout << leaf->_value << " ";

    PrintInOrder(leaf->_left);

    PrintInOrder(leaf->_right);
}

// Left - Right - Root
void  SortedBinaryTree::PrintPostOrder(Node *leaf)
{
    if (!leaf)
        return;

    PrintInOrder(leaf->_left);

    PrintInOrder(leaf->_right);

    cout << leaf->_value << " ";
}

void  SortedBinaryTree::PrintBTree(TreePrintOrder order)
{
    switch (order)
    {
        case TPInOrder:
            cout << "Print Binary tree method: InOrder" << endl;
            PrintInOrder(root);
        break;

        case TPPreOrder:
            cout << "Print Binary tree method: PreOrder" << endl;
            PrintPreOrder(root);
        break;

        case TPPostOrder:
            cout << "Print Binary tree method: PostOrder" << endl;
            PrintPostOrder(root);
        break;

        default:
            // set it as default way to iterate through the tree
            PrintInOrder(root);
    }

    cout << endl << endl;
}

// overload method in case there is no param provided
void  SortedBinaryTree::PrintBTree()
{
    PrintInOrder(root);
    cout << endl;
}

void  SortedBinaryTree::MirrorBTreeHelper(Node *leaf)
{
    if (!root || !leaf)
    {
        return;
    }

    MirrorBTreeHelper(leaf->_left);
    MirrorBTreeHelper(leaf->_right);
    swap(leaf->_left, leaf->_right);
}

void  SortedBinaryTree::MirrorBTree()
{
    MirrorBTreeHelper(root);
}

Node* SortedBinaryTree::GetBTreeRoot() const
{
    return root;
}

bool SortedBinaryTree::TwinTrees(Node *srcTree, Node *dstTree)
{
    if (!srcTree && !dstTree)
    {
        return true;
    }
    else if (!srcTree || !dstTree)
    {
        return false;
    }

    if ((srcTree->_value == dstTree->_value) &&
        TwinTrees(srcTree->_left, dstTree->_left) &&
        TwinTrees(srcTree->_right, dstTree->_right))
    {
        return true;
    }

    return false;
}


bool IdenticalTrees(SortedBinaryTree &srcTree, SortedBinaryTree &dstTree)
{
    Node *srcRoot = srcTree.GetBTreeRoot();
    Node *dstRoot = dstTree.GetBTreeRoot();
    return srcTree.TwinTrees(srcRoot, dstRoot);
}
