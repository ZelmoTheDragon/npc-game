/**
 * author: MOSELLE Maxime
 *  
 * Implémentation du prototype du moteur du jeu.
 */

#include <time.h>
#include "engine.h"

/**
 * Obtenir le temps en seconde depuis le 01/01/1970.
 */
int _current_time(){
    time_t seconds;
    seconds = time(NULL);
    return seconds;
}

/**
 * Arrêter le moteur du jeu.
 * 
 * \param self  Instance
 */
void _stop(Engine* self){
    SDL_Log("Stopping game...\n");
    self->running = false;
}

/**
 * Gérer les événements.
 * 
 * \param self  Instance
 */
void _process_events(Engine* self){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
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
void _update(Engine* self, double* delta_time){
    Manager_update(self->manager, delta_time);
}

/**
 * Mettre à jour tout le rendu graphique du jeu.
 * 
 * \param self  Instance
 */
void _draw(Engine* self){
    Renderer_clear(self->renderer);
    Manager_draw(self->manager, self->renderer);
    Renderer_draw(self->renderer);
}

// ====================
// Implémentation
// ====================


Engine* Engine_new(SDL_Window* window, Renderer* renderer){
    Engine* self = (Engine*) malloc(sizeof(Engine));
    self->window = window;
    self->renderer = renderer;
    self->manager = Manager_new();
    self->running = false;
    return self;
}

void Engine_del(Engine* self){
    Manager_del(self->manager);
    Renderer_del(self->renderer);
    free(self);
}

void Engine_start(Engine* self){
    SDL_Log("Starting game...\n");
    self->running = true;

    // Valeur d'interpolation.
    double delta = 0.0;

    // Temps actuel en seconde.
    int now = 0;

    // Dernier temps en seconde de la mise à jour de la boucle.
    int last_time = _current_time();

    // Déboggage: 
    // Calcul de la fréquence de la boucle.
    // 
    // Compteur de temps
    int timer = _current_time();

    // Compteur de FPS (Frame Per Second)
    int fps = 0;
 
    // Compteur de UPS (Update Per Second)
    int ups = 0;

    // Boucle principale du jeu
    // Toujours actif temps que le moteur est en fonctionnement.

    while(self->running){
        // Calcul de temps
        now = _current_time();
        delta += (now - last_time) / PULSE;
        last_time = now;

        // Traitement des événements
        _process_events(self);

        // Mise à jour du jeu
        // Appelé 60 fois par seconde
        while (delta >= 1.0) {
            _update(self, &delta);
            delta--;
            ups++;
        }

        // Mise à jour du rendu graphique
        // Appelé autant de fois que possible
        _draw(self);
        fps++;

        // Deboggage:
        // Affiche dans la console la fréquence de la boucle
        // toute les secondes
        if(_current_time() - timer >= 1){
            SDL_Log("FPS: %u, UPS: %u\n", fps, ups);
            ups = 0;
            fps = 0;
            timer += 1;
        }

        // Si le rendu graphique est synchronisé
        // Bloquer le rendu à 60 fois par seconde
        if(LOCK_FRAME_RATE){
            int sleep_time = (now - _current_time() + PULSE) * 1000;
            if(sleep_time < 1){
                sleep_time = 1;
            }
            SDL_Delay(sleep_time);
        }
    }

    // Fin de la boucle
    // Libération des ressources
    Engine_del(self);
}


