/**
 * \file renderer.h
 * \author: MOSELLE Maxime
 *  
 * Prototype du moteur de rendu graphique.
 * Une façade à SDL pour proposer des fonctions de dessins simplifiées/
 *  
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/** Taille d'un pixel de couleur en bit. */
static const int DEPTH = 32;

/**
 * Structure du moteur de rendu graphique.
 */
typedef struct Renderer
{

    /** Moteur de rendu graphique SDL. */
    SDL_Renderer *renderer;

    /** Surface tampon pour le rendu avant affichage sur la fenêtre. */
    SDL_Surface *surface;

    /** Largeur de la zone de dessin. */
    int width;

    /** Hauteur de la zone de dessin. */
    int height;

    /** Coéfficient de mise à l'échelle. */
    int scale;

    /** Décalage en abcisse. */
    int x_offset;

    /** Décalage en ordonnée. */
    int y_offset;
} Renderer;

/**
 * Constructeur.
 * 
 * \return Une nouvelle instance
 */
Renderer *Renderer_new(SDL_Renderer *renderer, int width, int height, int scale);

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void Renderer_del(Renderer *self);

/**
 * Modifier le décalage pour le rendu graphique.
 * 
 * \param self      Instance
 * \param x_offset  Décalage en abcisse
 * \param y_offset  Décalage en ordonnée
 */
void Renderer_set_offset(Renderer *self, int x_offset, int y_offset);

/**
 * Effacer la surface de rendu.
 * 
 * \param self  Instance
 */
void Renderer_clear(Renderer *self);

/**
 * Effectuer le rendu graphique dans la fenêtre.
 * 
 * \param self  Instance
 */
void Renderer_draw(Renderer *self);

/**
 * Dessiner un rectangle à couleur unique.
 * 
 * \param self  Instance
 * \param rect  Rectangle
 * \param color Couleur
 */
void Renderer_draw_rect(Renderer *self, SDL_Rect rect, SDL_Color color);

/**
 * Dessiner un rectangle plein à couleur unique.
 * 
 * \param self  Instance
 * \param rect  Rectangle
 * \param color Couleur
 */
void Renderer_fill_rect(Renderer *self, SDL_Rect rect, SDL_Color color);

#endif