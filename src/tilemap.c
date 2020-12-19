/**
 * \file renderer.c
 * \author MOSELLE Maxime
 *  
 * Implémentation du prototype pour la carte de tuile graphique.
 */

#include "tilemap.h"

/**
 * Lire une carte au format CSV.
 * Permet également de déterminer la taille de la carte dynamiquement.
 * 
 * \param self  Instance
 * \param array Tableau contenant les index des tuiles graphiques
 * \param path  Emplacement de la carte
 */
void _read_file(TileMap *self, IntArray *array, const char path[])
{
    int map_width = 0;
    int map_height = 0;
    int tile_index;

    FILE *csv;
    if ((csv = fopen(path, "r")) != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), csv))
        {
            char *token = strtok(line, CSV_CELL_SEPARATOR);
            while (token != NULL)
            {
                tile_index = strtol(token, NULL, 10);
                IntArray_add(array, tile_index);
                token = strtok(NULL, CSV_CELL_SEPARATOR);

                // Calculer dynamiquement la largeur de la carte en unité de tuile graphique.
                map_width++;
                if (self->map_width < map_width)
                {
                    self->map_width = map_width;
                }
            }

            // Calculer dynamiquement la hauteur de la carte en unité de tuile graphique.
            map_width = 0;
            map_height++;
            if (self->map_height < map_height)
            {
                self->map_height = map_height;
            }
        }
        fclose(csv);
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to read file: %s", path);
    }
}

/**
 * Effectuer le rendu graphique.
 * 
 * \param self      Instance
 * \param array     Carte de tuile
 * \param renderer  Façade de rendu graphique
 */
void _render_tile_map(TileMap *self, IntArray *array, Renderer *renderer)
{
    int index;
    int tile_index;

    int tileset_width;
    SDL_QueryTexture(self->tile_set, NULL, NULL, &tileset_width, NULL);
    int tileset_columns = tileset_width / TILE_WIDTH;

    SDL_Rect source = (SDL_Rect){0, 0, TILE_WIDTH, TILE_HEIGHT};
    SDL_Rect destination = (SDL_Rect){0, 0, TILE_WIDTH, TILE_HEIGHT};

    for (int y = 0; y < self->map_height; y++)
    {
        destination.y = y * TILE_HEIGHT;
        for (int x = 0; x < self->map_width; x++)
        {
            destination.x = x * TILE_WIDTH;
            index = x + y * self->map_width;
            tile_index = IntArray_get(array, index);
            if (tile_index != TILE_EMPTY)
            {
                source.x = (tile_index % tileset_columns) * TILE_WIDTH;
                source.y = (tile_index / tileset_columns) * TILE_HEIGHT;
                Renderer_draw_image(renderer, self->tile_set, source, destination);
            }
        }
    }
}

// ====================
// Implémentation
// ====================

TileMap *TileMap_new()
{
    TileMap *self = (TileMap *)malloc(sizeof(TileMap));
    self->tile_set = NULL;
    self->maps = (IntArray *)malloc(2 * sizeof(IntArray));
    self->map_width = 0;
    self->map_height = 0;

    // La carte actuelle est composée de deux couches superposées.
    // Chaque couche est instancié séparément.
    IntArray *layer0 = IntArray_new();
    self->maps[0] = *layer0;
    IntArray *layer1 = IntArray_new();
    self->maps[1] = *layer1;

    return self;
}

void TileMap_del(TileMap *self)
{
    free(self->maps);
    free(self);
}

void TileMap_process_event(TileMap *self, SDL_Event *event)
{
    // RAS
}

void TileMap_update(TileMap *self, double *delta_time)
{
    // Initialiser la couche 0 (le sol)
    if (IntArray_is_empty(&self->maps[0]))
    {
        _read_file(self, &self->maps[0], TILE_MAP_LAYER_0);
    }
    // Initialiser la couche 1 (les objets)
    if (IntArray_is_empty(&self->maps[1]))
    {
        _read_file(self, &self->maps[1], TILE_MAP_LAYER_1);
    }
}

void TileMap_draw(TileMap *self, Renderer *renderer)
{
    // Charger la texture
    if (!self->tile_set)
    {
        self->tile_set = Renderer_load_image(renderer, TILE_SET);
    }
    // Dessiner la couche 0 (le sol)
    _render_tile_map(self, &self->maps[0], renderer);
    // Dessiner la couche 1 (les objets)
    _render_tile_map(self, &self->maps[1], renderer);
}