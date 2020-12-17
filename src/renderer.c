/**
 * \file renderer.c
 * \author: MOSELLE Maxime
 *  
 * Implémentation du prototype du moteur de rendu.
 */

#include "renderer.h"

// ====================
// Implémentation
// ====================

Renderer *Renderer_new(SDL_Renderer *renderer, int width, int height, int scale)
{
    Renderer *self = (Renderer *)malloc(sizeof(Renderer));
    self->renderer = renderer;
    self->surface = SDL_CreateRGBSurface(0, width, height, DEPTH, 0, 0, 0, 0);
    self->width = width;
    self->height = height;
    self->scale = scale;
    self->x_offset = 0;
    self->y_offset = 0;
    return self;
}

void Renderer_del(Renderer *self)
{
    SDL_FreeSurface(self->surface);
    SDL_DestroyRenderer(self->renderer);
    free(self);
}

SDL_Texture *Renderer_load_image(Renderer *self, const char path[])
{
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(self->renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Renderer_set_offset(Renderer *self, int x_offset, int y_offset)
{
    self->x_offset = x_offset;
    self->y_offset = y_offset;
}

void Renderer_clear(Renderer *self)
{
    SDL_SetRenderDrawColor(self->renderer, 0, 0, 0, 0);
    SDL_RenderClear(self->renderer);
}

void Renderer_draw(Renderer *self)
{
    SDL_RenderPresent(self->renderer);
}

void Renderer_draw_image(Renderer *self, SDL_Texture *image, SDL_Rect source, SDL_Rect destination)
{
    SDL_RenderCopy(self->renderer, image, &source, &destination);
}

void Renderer_draw_rect(Renderer *self, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(self->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(self->renderer, &rect);
}

void Renderer_fill_rect(Renderer *self, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(self->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(self->renderer, &rect);
}