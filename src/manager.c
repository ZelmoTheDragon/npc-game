/**
 * author: MOSELLE Maxime
 *  
 * Implémentation du prototype du gestionnaire du jeu.
 */

#include "manager.h"

// ====================
// Implémentation
// ====================

Manager *Manager_new()
{
    Manager *self = (Manager *)malloc(sizeof(Manager));
    self->player = Player_new();
    return self;
}

void Manager_del(Manager *self)
{
    Player_del(self->player);
    free(self);
}

void Manager_process_event(Manager *self, SDL_Event *event)
{
    Player_process_event(self->player, event);
}

void Manager_update(Manager *self, double *delta_time)
{
    Player_update(self->player, delta_time);
}

void Manager_draw(Manager *self, Renderer *renderer)
{
    Player_draw(self->player, renderer);
}