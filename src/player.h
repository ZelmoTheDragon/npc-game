/**
 * \file player.h
 * \author: MOSELLE Maxime
 *  
 * Prototype du joueur.
 * Désigne une entité contrôlable par l'utilisateur.
 *  
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "renderer.h"

/**
 * Un personnage.
 */
typedef struct Player
{
    /** Rectangle pour la position et la taille du joueur. */
    SDL_Rect rect;

    /** Vecteur de direction pour le déplacement. */
    SDL_Point vector;

    /** Couleur. */
    SDL_Color color;

    /** Vitesse de déplacement. */
    int speed;
} Player;

/**
 * Constructeur.
 * 
 * \return Une nouvelle instance
 */
Player *Player_new();

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void Player_del(Player *self);

/**
 * Gérer les événements.
 * 
 * \param self  Instance
 * \param event Événement SDL
 */
void Player_process_event(Player *self, SDL_Event *event);

/**
 * Mettre à jour toute la logique de traitement.
 * 
 * \param self          Instance
 * \param delta_time    Valeur d'interpolation
 */
void Player_update(Player *self, double *delta_time);

/**
 * Mettre à jour tout le rendu graphique.
 * 
 * \param self      Instance
 * \param renderer  Façade de rendu graphique
 */
void Player_draw(Player *self, Renderer *renderer);

#endif