/**
 * \file manager.c
 * \author: MOSELLE Maxime
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
    self->debug = Debug_new();
    self->tilemap = TileMap_new();
    self->player = Player_new();
    return self;
}

void Manager_del(Manager *self)
{
    Debug_del(self->debug);
    TileMap_del(self->tilemap);
    Player_del(self->player);
    free(self);
}

void Manager_process_event(Manager *self, SDL_Event *event)
{
    TileMap_process_event(self->tilemap, event);
    Player_process_event(self->player, event);
}

void Manager_update(Manager *self, double *delta_time)
{
    Debug_tick(self->debug);
    TileMap_update(self->tilemap, delta_time);
    Player_update(self->player, delta_time);
}

void Manager_draw(Manager *self, Renderer *renderer)
{
    Debug_render(self->debug);
    TileMap_draw(self->tilemap, renderer);
    Player_draw(self->player, renderer);
}