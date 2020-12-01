/*
 * main.cpp
 *
 *  Created on: Nov. 27, 2020
 *      Author: Emil Fanache
 */

#include "HashTable.hpp"


int main()
{
    HashTable ht;

    ht.AddName("Sam");
    ht.AddName("Emil");
    ht.AddName("John");
    ht.AddName("Sandra");
    ht.AddName("Aurelia");
    ht.AddName("Cornelius");
    ht.AddName("Anny");
    ht.AddName("Marius");

    ht.DisplayAll();

    if (ht.HasName("Emil"))
        cout << "The name Emil exists in the hash table!" << endl;
    else
        cout << "The name Emil doesn't exist in the hash table!" << endl;



    return 0;
}
