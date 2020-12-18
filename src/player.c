/**
 * \file player.c
 * \author: MOSELLE Maxime
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
    self->rect = (SDL_Rect){0, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
    self->vector = (SDL_Point){0, 0};
    self->color = (SDL_Color){255, 0, 0, 0};
    self->speed = 1;
    self->frame = 0;
    self->playing = false;
    self->offset = (SDL_Point){0, 0};
    self->sprite_sheet_area = (SDL_Rect){0, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT};
    self->sprite_sheet = NULL;
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
            self->playing = true;
            self->offset = PLAYER_OFFSET_RIGHT;
        }
        if (event->key.keysym.sym == SDLK_LEFT)
        {
            _set_vector(self, -1, 0);
            self->playing = true;
            self->offset = PLAYER_OFFSET_LEFT;
        }
        if (event->key.keysym.sym == SDLK_DOWN)
        {
            _set_vector(self, 0, 1);
            self->playing = true;
            self->offset = PLAYER_OFFSET_DOWN;
        }
        if (event->key.keysym.sym == SDLK_UP)
        {
            _set_vector(self, 0, -1);
            self->playing = true;
            self->offset = PLAYER_OFFSET_UP;
        }
    }
    if (event->type == SDL_KEYUP)
    {
        if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_UP)
        {
            _set_vector(self, 0, 0);
            self->playing = false;
            self->frame = 0;
            self->sprite_sheet_area.x = self->offset.x;
            self->sprite_sheet_area.y = self->offset.y;
        }
    }
}

void Player_update(Player *self, double *delta_time)
{
    if (!self->sprite_sheet)
    {
        // Ne pas faire de mise à jour si la texture n'est pas chargée.
        return;
    }
    _move(self, delta_time);

    int sprite_sheet_width;
    SDL_QueryTexture(self->sprite_sheet, NULL, NULL, &sprite_sheet_width, NULL);
    int frames = sprite_sheet_width / PLAYER_SPRITE_WIDTH;

    if (self->playing)
    {
        self->frame++;
        if (self->frame > PLAYER_ANIMATION_SPEED)
        {
            self->frame = 0;
        }
    }

    int index = self->frame * frames / PLAYER_ANIMATION_SPEED;
    int current_index = fmin(index, frames - 1);
    self->sprite_sheet_area.x = (current_index % frames) * PLAYER_SPRITE_WIDTH + self->offset.x;
    self->sprite_sheet_area.y = (current_index / frames) * PLAYER_SPRITE_HEIGHT + self->offset.y;
}

void Player_draw(Player *self, Renderer *renderer)
{
    if (!self->sprite_sheet)
    {
        self->sprite_sheet = Renderer_load_image(renderer, PLAYER_SPRITE_SHEET);
    }
    Renderer_draw_image(renderer, self->sprite_sheet, self->sprite_sheet_area, self->rect);
}