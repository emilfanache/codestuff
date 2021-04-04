/*
 * main.cpp
 *
 *  Created on: Nov. 9, 2020
 *      Author: Emil Fanache
 */

#include <iostream>
#include "SingleLinkedList.hpp"

using namespace std;

int main()
{

    cout << "===== Testing class template with int type =====" << endl << endl;
    SingleLinkedList<int> SlistInt(false);

    SlistInt.AddNode(7);
    SlistInt.AddNode(8);
    SlistInt.AddNode(9);
    SlistInt.AddNode(10);
    SlistInt.AddNode(14);
    SlistInt.PrintList("Initial creation by adding end nodes");
    SlistInt.DeleteNode(7);
    SlistInt.DeleteNode(9);
    SlistInt.PrintList("After Nodes are being deleted");
    SlistInt.AddNode(10, 12);
    SlistInt.AddNode(14, 15);
    SlistInt.PrintList("After adding inside nodes");
    SlistInt.ReverseList();
    SlistInt.PrintList("After reversing list");

    cout << endl << endl;
    cout << "===== Testing class template with string type =====" << endl << endl;

    SingleLinkedList<string> SlistStr(false);
    SlistStr.AddNode("seven");
    SlistStr.AddNode("eight");
    SlistStr.AddNode("nine");
    SlistStr.AddNode("ten");
    SlistStr.AddNode("fourteen");
    SlistStr.PrintList("Initial creation by adding end nodes");
    SlistStr.ReverseList();
    SlistStr.PrintList("After reversing list");


    return 0;
}
