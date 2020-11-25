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

  Slist.AddEndNode(7);
  Slist.AddEndNode(8);
  Slist.AddEndNode(9);
  Slist.AddEndNode(10);
  Slist.AddEndNode(14);
  Slist.PrintList("Initial creation by adding end nodes");
  Slist.DeleteNode(7);
  Slist.DeleteNode(9);
  Slist.PrintList("After Nodes are being deleted");
  Slist.AddInsideNode(10, 12);
  Slist.AddInsideNode(14, 15);
  Slist.PrintList("After adding inside nodes");
  Slist.ReverseList();
  Slist.PrintList("After reversing list");

  return 0;
}
