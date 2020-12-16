/**
 * author: MOSELLE Maxime
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
    SDL_DestroyRenderer(self->renderer);
    SDL_FreeSurface(self->surface);
    free(self);
}

void Renderer_set_offset(Renderer *self, int x_offset, int y_offset)
{
    self->x_offset = x_offset;
    self->y_offset = y_offset;
}

void Renderer_clear(Renderer *self)
{
    Uint32 rgb = SDL_MapRGB(self->surface->format, 0, 0, 0);
    SDL_FillRect(self->surface, NULL, rgb);
}

void Renderer_draw(Renderer *self)
{
    SDL_Texture *image = SDL_CreateTextureFromSurface(self->renderer, self->surface);
    SDL_RenderCopy(self->renderer, image, NULL, NULL);
    SDL_RenderPresent(self->renderer);
    SDL_DestroyTexture(image);
}

void Renderer_draw_rect(Renderer *self, SDL_Rect rect, SDL_Color color)
{
}

void Renderer_fill_rect(Renderer *self, SDL_Rect rect, SDL_Color color)
{
    Uint32 rgb = SDL_MapRGB(self->surface->format, color.r, color.g, color.b);
    SDL_FillRect(self->surface, &rect, rgb);
}