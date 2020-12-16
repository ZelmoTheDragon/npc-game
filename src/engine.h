/**
 * author: MOSELLE Maxime
 *  
 * Prototype du moteur du jeu.
 * Le moteur orchestre tous les autres éléments du jeu.
 * Il est cadencé à une fréquence de pulsation.
 * Ce cadencement permet de conserver un traitement cohérent pour les calculs.
 *  
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "renderer.h"
#include "manager.h"

/** Fréquence de pulsation de la boucle principale du moteur. */
static const double PULSE = 1000.0 / 60.0;

/** Largeur. */
static const int WIDTH = 320;

/** Hauteur avec un ratio 16/9. */
static const int HEIGHT = WIDTH / 16 * 9;

/** Coéfficient de mise à l'échelle. */
static const int SCALE = 3;

/**
 * Structure du moteur du jeu.
 */
typedef struct Engine
{

    /** Fenêtre principale SDL. */
    SDL_Window *window;

    /** Moteur de rendu graphique. */
    Renderer *renderer;

    /** Gestionnaire. */
    Manager *manager;

    /** Indique si le moteur est en fonctionnement. */
    bool running;
} Engine;

/**
 * Constructeur.
 * 
 * \param window    Fenêtre SDL
 * \param renderer  Façade de rendu graphique
 */
Engine *Engine_new(SDL_Window *window, Renderer *renderer);

/**
 * Destructeur.
 * 
 * \param self  Instance
 */
void Engine_del(Engine *self);

/**
 * Démarrer le moteur.
 * 
 * \param self  Instance
 */
void Engine_start(Engine *self);

#endif