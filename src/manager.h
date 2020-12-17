/**
 * author: MOSELLE Maxime
 *  
 * Prototype du gestionnaire du jeu.
 * Le gestionnaire orchestre principalement les entités du jeu.
 * Comme par exemple, le joueur, les monstres, les tuiles graphiques etc...
 *  
 */

#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "renderer.h"
#include "debug.h"
#include "player.h"

/**
 * Structure du gestionnaire du jeu.
 */
typedef struct Manager
{
    /** Débogueur. */
    Debug *debug;

    /** Joueur. */
    Player *player;
} Manager;

/**
 * Constructeur.
 * 
 * \return Une nouvelle instance
 */
Manager *Manager_new();

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void Manager_del(Manager *self);

/**
 * Gérer les événements.
 * 
 * \param self  Instance
 * \param event Événement SDL
 */
void Manager_process_event(Manager *self, SDL_Event *event);

/**
 * Mettre à jour toute la logique de traitement du jeu.
 * 
 * \param self          Instance
 * \param delta_time    Valeur d'interpolation
 */
void Manager_update(Manager *self, double *delta_time);

/**
 * Mettre à jour tout le rendu graphique du jeu.
 * 
 * \param self      Instance
 * \param renderer  Façade de rendu graphique
 */
void Manager_draw(Manager *self, Renderer *renderer);

#endif