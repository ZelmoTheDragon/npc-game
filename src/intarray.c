/**
 * \file intarray.c
 * \author: MOSELLE Maxime
 *  
 * Implémentation du prototype du tableau dynamique.
 */

#include "intarray.h"

// ====================
// Implémentation
// ====================

IntArray *IntArray_new()
{
    IntArray *self = (IntArray *)malloc(sizeof(IntArray));
    self->size = 0;
    self->data = NULL;
    return self;
}

void IntArray_del(IntArray *self)
{
    free(self->data);
    free(self);
}

void IntArray_add(IntArray *self, int value)
{
    self->size++;
    if (self->data == NULL)
    {
        self->data = (int *)malloc(1 * sizeof(int));
    }
    else
    {
        self->data = (int *)realloc(self->data, self->size * sizeof(int));
    }
    self->data[self->size - 1] = value;
}

int IntArray_remove(IntArray *self, int index)
{
    int value = self->data[index];
    for (int i = index - 1; i < self->size - 1; i++)
    {
        self->data[i] = self->data[i + 1];
    }
    self->size--;
    self->data = (int *)realloc(self->data, self->size * sizeof(int));
    return value;
}

int IntArray_get(IntArray *self, int index)
{
    return self->data[index];
}

void IntArray_set(IntArray *self, int index, int new_value)
{
    self->data[index] = new_value;
}

int IntArray_size(IntArray *self)
{
    return self->size;
}

bool IntArray_is_empty(IntArray *self)
{
    return self->size == 0;
}