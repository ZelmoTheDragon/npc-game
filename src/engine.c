/**
 * author: MOSELLE Maxime
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

    // Déboggage:
    // Calcul de la fréquence de la boucle.
    //
    // Compteur de temps
    Uint32 timer = SDL_GetTicks();

    // Compteur de FPS (Frame Per Second)
    int fps = 0;

    // Compteur de UPS (Update Per Second)
    int ups = 0;

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
        ups++;

        // Mise à jour du rendu graphique
        // Appelé 60 fois par seconde
        _draw(self);
        fps++;

        // Deboggage:
        // Affiche dans la console la fréquence de la boucle
        // toute les secondes
        if (SDL_GetTicks() - timer >= 1000)
        {
            SDL_Log("FPS: %u, UPS: %u\n", fps, ups);
            ups = 0;
            fps = 0;
            timer += 1000;
        }

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
