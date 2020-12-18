/**
 * \file tilemap.h
 * \author: MOSELLE Maxime
 *  
 * Prototype pour la carte de tuile graphique.
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "intarray.h"
#include "renderer.h"

/** Largeur d'une tuile graphique. */
static const int TILE_WIDTH = 16;

/** Hauteur d'une tuile graphique. */
static const int TILE_HEIGHT = 16;

/** Emplacement de l'image de texture de la carte. */
static const char TILE_SET[] = "res/images/overworld.png";

/** Emplacement de la carte de test niveau 0 */
static const char TILE_MAP_LAYER_0[] = "res/maps/test_0.csv";

/** Emplacement de la carte de test niveau 1 */
static const char TILE_MAP_LAYER_1[] = "res/maps/test_1.csv";

/** Index d'une tuile vide. */
static const int TILE_EMPTY = -1;

/** Caractère de séparation de cellule pour un fichier CSV. */
static const char CSV_CELL_SEPARATOR[] = ",";

/** Caractère de séparation de ligne pour un fichier CSV. */
static const char CSV_LINE_SEPARATOR[] = "\n";

/**
 * Une carte composée de tuile graphique.
 */
typedef struct TileMap
{
    /** Texture de la carte. */
    SDL_Texture *tile_set;

    /** Tableau contenant les index des tuiles graphiques. */
    IntArray *map;

    /** Largeur de la carte (en tuile). */
    int map_width;

    /** Hauteur de la carte (en tuile). */
    int map_height;

} TileMap;

/**
 * Constructeur.
 * 
 * \return Une nouvelle instance
 */
TileMap *TileMap_new();

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void TileMap_del(TileMap *self);

/**
 * Gérer les événements.
 * 
 * \param self  Instance
 * \param event Événement SDL
 */
void TileMap_process_event(TileMap *self, SDL_Event *event);

/**
 * Mettre à jour toute la logique de traitement.
 * 
 * \param self          Instance
 * \param delta_time    Valeur d'interpolation
 */
void TileMap_update(TileMap *self, double *delta_time);

/**
 * Mettre à jour tout le rendu graphique.
 * 
 * \param self      Instance
 * \param renderer  Façade de rendu graphique
 */
void TileMap_draw(TileMap *self, Renderer *renderer);

#endif