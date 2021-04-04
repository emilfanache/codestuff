/*
 * main.cpp
 *
 *  Created on: Nov. 9, 2020
 *      Author: Emil Fanache
 */

#include "SingleLinkedList.hpp"


int main()
{
    SingleLinkedList Slist(false);

    Slist.AddNode(7);
    Slist.AddNode(8);
    Slist.AddNode(9);
    Slist.AddNode(10);
    Slist.AddNode(14);
    Slist.PrintList("Initial creation by adding end nodes");
    Slist.DeleteNode(7);
    Slist.DeleteNode(9);
    Slist.PrintList("After Nodes are being deleted");
    Slist.AddNode(10, 12);
    Slist.AddNode(14, 15);
    Slist.PrintList("After adding inside nodes");
    Slist.ReverseList();
    Slist.PrintList("After reversing list");

    return 0;
}
