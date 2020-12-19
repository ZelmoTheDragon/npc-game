/**
 * \file renderer.c
 * \author MOSELLE Maxime
 *  
 * Implémentation du prototype du moteur de rendu.
 */

#include "renderer.h"

// ====================
// Implémentation
// ====================

Renderer *Renderer_new(SDL_Renderer *graphic2d, int width, int height)
{
    Renderer *self = (Renderer *)malloc(sizeof(Renderer));
    self->graphic2d = graphic2d;
    self->surface = SDL_CreateRGBSurface(0, width, height, DEPTH, 0, 0, 0, 0);
    self->width = width;
    self->height = height;
    self->x_offset = 0;
    self->y_offset = 0;
    return self;
}

void Renderer_del(Renderer *self)
{
    SDL_FreeSurface(self->surface);
    SDL_DestroyRenderer(self->graphic2d);
    free(self);
}

SDL_Texture *Renderer_load_image(Renderer *self, const char path[])
{
    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(self->graphic2d, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Renderer_set_offset(Renderer *self, int x_offset, int y_offset)
{
    self->x_offset = x_offset - self->width / 2;
    self->y_offset = y_offset - self->height / 2;
}

void Renderer_clear(Renderer *self)
{
    SDL_SetRenderDrawColor(self->graphic2d, 0, 0, 0, 0);
    SDL_RenderClear(self->graphic2d);
}

void Renderer_draw(Renderer *self)
{
    SDL_RenderPresent(self->graphic2d);
}

void Renderer_draw_image(Renderer *self, SDL_Texture *image, SDL_Rect source, SDL_Rect destination)
{
    destination.x -= self->x_offset;
    destination.y -= self->y_offset;
    SDL_RenderCopy(self->graphic2d, image, &source, &destination);
}

void Renderer_draw_rect(Renderer *self, SDL_Rect rect, SDL_Color color)
{
    rect.x -= self->x_offset;
    rect.y -= self->y_offset;
    SDL_SetRenderDrawColor(self->graphic2d, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(self->graphic2d, &rect);
}

void Renderer_fill_rect(Renderer *self, SDL_Rect rect, SDL_Color color)
{
    rect.x -= self->x_offset;
    rect.y -= self->y_offset;
    SDL_SetRenderDrawColor(self->graphic2d, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(self->graphic2d, &rect);
}