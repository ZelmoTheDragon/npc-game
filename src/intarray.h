/**
 * \file intarray.h
 * \author: MOSELLE Maxime
 *  
 * Prototype de tableau dynamique.
 */

#ifndef INTARRAY_H
#define INTARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Simple tableau de type 'int'.
 */
typedef struct IntArray
{
    /** Taille. */
    int size;

    /** Données. */
    int *data;
} IntArray;

/**
 * Constructeur.
 * 
 * \return Une nouvelle instance
 */
IntArray *IntArray_new();

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void IntArray_del(IntArray *self);

/**
 * Ajouter une nouvelle valeur au tableau.
 * 
 * \param self  Instance
 * \param value Nouvelle valeur
 */
void IntArray_add(IntArray *self, int value);

/**
 * Supprimer un élément du tableau.
 * 
 * \param self  Instance
 * \param index Emplacement de l'élément à supprimer
 * \return      La valeur de l'élément situé à cet index
 */
int IntArray_remove(IntArray *self, int index);

/**
 * Récupérer un élément.
 * 
 * \param self  Instance
 * \param index Emplacement de l'élément
 * \return      La valeur de l'élément situé à cet index
 */
int IntArray_get(IntArray *self, int index);

/**
 * Placer une nouvelle valeur à un emplacement particulier.
 * \param self      Instance
 * \param index     Emplacement de l'élément
 * \param new_value Nouvelle valeur
 */
void IntArray_set(IntArray *self, int index, int new_value);

/**
 * Récupérer la taille du tableau.
 * 
 * \param self  Instance
 * \return      La taille du tableau
 */
int IntArray_size(IntArray *self);

/**
 * Indiquer si le tableau est vide.
 * 
 * \param self  Instance
 * \return      La valeur 'true' si le tableau est vide, sinon la valeur 'false' est retournée
 */
bool IntArray_is_empty(IntArray *self);

#endif