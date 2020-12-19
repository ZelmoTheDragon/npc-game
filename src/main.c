/**
 * \file main.c
 * \author MOSELLE Maxime
 * 
 * Principal.
 */

#include "engine.h"

/**
 * Point d'entrée.  
 * 
 * \param argc  Nombre de paramètre
 * \param argv  Paramètres système
 * \return      Code de retour: '0' en cas de succès ou une autre valeur en cas d'erreur
 */
int main(int argc, char *argv[])
{
    // Initialiation de SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Fail to load SDL2: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Initialisation de SDL Image.
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Fail to load SDL2 Image: %s", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Création de la fenêtre principale.
    SDL_Window *window = SDL_CreateWindow(
        "NPC Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCALE * WIDTH,
        SCALE * HEIGHT,
        0);

    if (window == NULL)
    {
        SDL_Log("Fail to create window: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Création du moteur de rendu SDL.
    // La zone de dessin du moteur de rendu est plus petite que la fenêtre.
    // Par conséquant, le rendu final est étiré sur toute la surface de l'écran.
    SDL_Renderer *graphic2d = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetIntegerScale(graphic2d, true);
    SDL_RenderSetLogicalSize(graphic2d, WIDTH, HEIGHT);

    // Création du moteur de jeu.
    Renderer *renderer = Renderer_new(graphic2d, WIDTH, HEIGHT);
    Engine *engine = Engine_new(window, renderer);
    Engine_start(engine);

    // Libération des ressources.
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("END.\n");
    return EXIT_SUCCESS;
}