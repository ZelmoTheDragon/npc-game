/**
 * \file debug.c
 * \author MOSELLE Maxime
 *  
 * Implémentation du prototype des informations de débogage.
 */

#include "debug.h"

// ====================
// Implémentation
// ====================

Debug *Debug_new()
{
    Debug *self = (Debug *)malloc(sizeof(Debug));
    self->timer = SDL_GetTicks();
    self->updates = 0;
    self->frames = 0;
    return self;
}

void Debug_del(Debug *self)
{
    free(self);
}

void Debug_tick(Debug *self)
{
    self->updates++;
    // Debogage:
    // Affiche dans la console la fréquence de la boucle
    // toute les secondes
    if (SDL_GetTicks() - self->timer >= 1000)
    {
        SDL_Log("UPS: %i, FPS: %i\n", self->updates, self->frames);
        self->updates = 0;
        self->frames = 0;
        self->timer += 1000;
    }
}

void Debug_render(Debug *self)
{
    self->frames++;
}