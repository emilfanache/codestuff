/*
 *  GenericStruct.c
 *
 *  Created on: Apr. 24, 2021
 *      Author: Emil Fanache
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * I'm addingf this typedef to avoid the issue of self-reference to
 * the struct type. If I don't do this I neet to write "struct Generic"
 * evgery time I use it inside the struct
 * */
typedef struct Generic Generic;

struct Generic {
    int _field;
    void (*GenSetField)(Generic *, int);
    int  (*GenGetField)(Generic *);
    void (*GenPrintField)(Generic *);
    void (*GenUninit)(Generic *);
};

void SetField(Generic *pGen, int value)
{
    if (!pGen)
    {
        return;
    }

    pGen->_field = value;
}

int GetField(Generic *pGen)
{
    if (!pGen)
    {
        return 0;
    }

    return pGen->_field;
}

void PrintField(Generic *pGen)
{
    if (!pGen)
    {
        printf("The Generic structure has not been set!\n");
    }
    else
    {
        printf("Field value is: %d\n", pGen->GenGetField(pGen));
    }
}

void GenericUninit(Generic *pGen)
{
    if (!pGen)
    {
        return;
    }

    free(pGen);
    pGen = NULL;
}

Generic* GenericInit()
{
    Generic *pGen = (Generic *)malloc(sizeof(Generic));
    if (!pGen)
    {
        printf("Memory allocation error at %s:%d\n", __FILE__, __LINE__);
        return NULL;
    }

    pGen->_field = 0;
    pGen->GenGetField = &GetField;
    pGen->GenSetField = &SetField;
    pGen->GenPrintField = &PrintField;
    pGen->GenUninit = &GenericUninit;

    return pGen;
}

int main(void)
{
    Generic *pGen = NULL;

    pGen = GenericInit();
    if (!pGen)
    {
        return -1;
    }

    pGen->GenSetField(pGen,22);
    pGen->GenPrintField(pGen);
    pGen->GenUninit(pGen);

    return 0;
}
