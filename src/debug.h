/**
 * \file debug.h
 * \author: MOSELLE Maxime
 *  
 * Prototype pour les informations de débogage.
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/**
 * Structure de débogage.
 */
typedef struct Debug
{
    /** Horloge interne. */
    Uint32 timer;

    /** Compteur de mise à jour. */
    int updates;

    /** Compteur de rendu graphique. */
    int frames;

} Debug;

/**
 * Constructeur.
 * 
 * \return Une nouvelle instance
 */
Debug *Debug_new();

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void Debug_del(Debug *self);

/**
 * Calculer le temps dans la boucle de mise à jour et afficher un message de débogage dans la sortie SDL.
 * Cette fonction doit être appelée dans la fonction 'update'.
 * 
 * \param self  Instance
 */
void Debug_tick(Debug *self);

/**
 * Calculer le temps de la boucle de rendu graphique.
 * Cette fonction doit être appelée dans la fonction 'draw'.
 * 
 * \param self  Instance
 */
void Debug_render(Debug *self);

#endif