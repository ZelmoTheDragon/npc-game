/**
 * author: MOSELLE Maxime
 * 
 * Principal.
 */

#include "engine.h"

/**
 * Point d'entrée.  
 * 
 * \param argc
 * \param argv
 * \return Code de retour: '0' en cas de succès ou une autre valeur en cas d'erreur
 */
int main(int argc, char *argv[])
{
    // Initialiation du SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Fail to load SDL2: %s", SDL_GetError());
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
    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(
        window,
        -1,
        0);

    // Création du moteur de jeu.
    Renderer *renderer = Renderer_new(sdl_renderer, WIDTH, HEIGHT, SCALE);
    Engine *engine = Engine_new(window, renderer);
    Engine_start(engine);

    // Libération des ressources.
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("END.\n");
    return EXIT_SUCCESS;
}