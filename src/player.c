/**
 * author: MOSELLE Maxime
 *  
 * Implémentation du prototype du joueur.
 */

#include "player.h"

/**
 * Modifier le vecteur de direction.
 * 
 * \param self  Instance
 * \param vx    Direction en abcisse sur l'intervale [-1, 1]
 * \param vy    Direction en ordonnée sur l'intervale [-1, 1]
 */
void _set_vector(Player *self, int vx, int vy)
{
    self->vector.x = vx;
    self->vector.y = vy;
}

/**
 * Déplacer le joueur.
 * 
 * \param self          Instance
 * \param delta_time    Valeur d'interpolation
 */
void _move(Player *self, double *delta_time)
{
    self->rect.x += (self->speed * self->vector.x) * *delta_time;
    self->rect.y += (self->speed * self->vector.y) * *delta_time;
}

// ====================
// Implémentation
// ====================

Player *Player_new()
{
    Player *self = (Player *)malloc(sizeof(Player));
    self->rect.x = 0;
    self->rect.y = 0;
    self->rect.w = 16;
    self->rect.h = 16;
    self->vector.x = 0;
    self->vector.y = 0;
    self->color.r = 255;
    self->color.g = 0;
    self->color.b = 0;
    self->color.a = 0;
    self->speed = 1;
    return self;
}

void Player_del(Player *self)
{
    free(self);
}

void Player_process_event(Player *self, SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.sym == SDLK_RIGHT)
        {
            _set_vector(self, 1, 0);
        }
        if (event->key.keysym.sym == SDLK_LEFT)
        {
            _set_vector(self, -1, 0);
        }
        if (event->key.keysym.sym == SDLK_DOWN)
        {
            _set_vector(self, 0, 1);
        }
        if (event->key.keysym.sym == SDLK_UP)
        {
            _set_vector(self, 0, -1);
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_UP)
        {
            _set_vector(self, 0, 0);
        }
    }
}

void Player_update(Player *self, double *delta_time)
{
    _move(self, delta_time);
}

void Player_draw(Player *self, Renderer *renderer)
{
    Renderer_fill_rect(renderer, self->rect, self->color);
}