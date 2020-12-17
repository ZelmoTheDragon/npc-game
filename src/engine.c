/**
 * \file engine.c
 * \author: MOSELLE Maxime
 *  
 * Implémentation du prototype du moteur du jeu.
 */

#include "engine.h"

/**
 * Arrêter le moteur du jeu.
 * 
 * \param self  Instance
 */
void _stop(Engine *self)
{
    SDL_Log("Stopping game...\n");
    self->running = false;
}

/**
 * Gérer les événements.
 * 
 * \param self  Instance
 */
void _process_events(Engine *self)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            _stop(self);
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Basculer le mode d'affichage si F11 est appuyé
            if (event.key.keysym.sym == SDLK_F11)
            {
                Engine_toggle_screen(self);
            }
        }
    }
    Manager_process_event(self->manager, &event);
}

/**
 * Mettre à jour toute la logique de traitement du jeu.
 * 
 * \param self          Instance
 * \param delta_time    Valeur d'interpolation
 */
void _update(Engine *self, double *delta_time)
{
    Manager_update(self->manager, delta_time);
}

/**
 * \brief Mettre à jour tout le rendu graphique du jeu.
 * 
 * \param self  Instance
 */
void _draw(Engine *self)
{
    Renderer_clear(self->renderer);
    Manager_draw(self->manager, self->renderer);
    Renderer_draw(self->renderer);
}

// ====================
// Implémentation
// ====================

Engine *Engine_new(SDL_Window *window, Renderer *renderer)
{
    Engine *self = (Engine *)malloc(sizeof(Engine));
    self->window = window;
    self->renderer = renderer;
    self->manager = Manager_new();
    self->running = false;
    self->full_screen = false;
    return self;
}

void Engine_del(Engine *self)
{
    Manager_del(self->manager);
    Renderer_del(self->renderer);
    free(self);
}

void Engine_start(Engine *self)
{
    SDL_Log("Starting game...\n");
    self->running = true;

    // Valeur d'interpolation.
    // TODO: Calculer cette valeur.
    double delta = 1.0;

    // Temps actuel en milliseconde.
    Uint32 now = 0;

    // Dernier temps en milliseconde de la mise à jour de la boucle.
    Uint32 last_time = 0;

    // Temps en milliseconde de repos de la boucle.
    int sleep_time;

    // Boucle principale du jeu
    // Toujours actif temps que le moteur est en fonctionnement.

    while (self->running)
    {
        // Calcul de temps
        now = SDL_GetTicks();

        // Traitement des événements
        _process_events(self);

        // Mise à jour du jeu
        // Appelé 60 fois par seconde
        _update(self, &delta);

        // Mise à jour du rendu graphique
        // Appelé 60 fois par seconde
        _draw(self);

        // Calcul de temps
        // Synchronise la boucle à 60 FPS
        last_time = SDL_GetTicks() - now;
        if (last_time < PULSE)
        {
            sleep_time = PULSE - last_time;
        }
        else
        {
            sleep_time = PULSE;
        }
        SDL_Delay(sleep_time);
    }

    // Fin de la boucle
    // Libération des ressources
    Engine_del(self);
}

void Engine_toggle_screen(Engine *self)
{
    self->full_screen = !self->full_screen;
    if (self->full_screen)
    {
        SDL_SetWindowFullscreen(self->window, SDL_WINDOW_FULLSCREEN);
        SDL_Log("Full screen mode");
    }
    else
    {
        SDL_SetWindowFullscreen(self->window, 0);
        SDL_Log("Window mode");
    }
}