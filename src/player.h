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
#include <math.h>
#include <SDL2/SDL.h>
#include "renderer.h"

/** Emplacement de l'image de texture du joueur. */
static const char PLAYER_SPRITE_SHEET[] = "res/images/npc_test.png";

/** Largeur d'une tuile graphique. */
static const int PLAYER_SPRITE_WIDTH = 16;

/** Hauteur d'une tuile graphique. */
static const int PLAYER_SPRITE_HEIGHT = 32;

/** Vitesse de l'animation. */
static const int PLAYER_ANIMATION_SPEED = 50;

/** Emplacement de la tuile graphique vers le haut. */
static const SDL_Point PLAYER_OFFSET_UP = (SDL_Point){0, 64};

/** Emplacement de la tuile graphique vers le bas. */
static const SDL_Point PLAYER_OFFSET_DOWN = (SDL_Point){0, 0};

/** Emplacement de la tuile graphique vers la gauche. */
static const SDL_Point PLAYER_OFFSET_LEFT = (SDL_Point){0, 96};

/** Emplacement de la tuile graphique vers la droite. */
static const SDL_Point PLAYER_OFFSET_RIGHT = (SDL_Point){0, 32};

/** Emplacement de la tuile graphique par défaut. */
static const SDL_Point PLAYER_OFFSET_DEFAULT = (SDL_Point){0, 0};

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

    /** Image courante de l'animation. */
    int frame;

    /** Indique si l'animation est en cours. */
    bool playing;

    /** Direction de l'animation. */
    SDL_Point offset;

    /** Zone de la feuille de texture courante. */
    SDL_Rect sprite_sheet_area;

    /** Image de texture du joueur. */
    SDL_Texture *sprite_sheet;
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