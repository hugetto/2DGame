//==============================================================================
/*
    Entry Point
    Hug Beneit
*/
//==============================================================================

#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstring>
#include <SDL_net.h>
#include <SDL.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#pragma warning( disable : 26812 )



int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    SDL_Event event;
    int quit = 0;

    /* Initialise SDL */
    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (SDLNet_Init() < 0) {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return -1;
    }

    while (!quit) {
        /* Poll for events */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                break;
            default:
                break;
            }
        }


    }

    /* Clean up */
    SDLNet_Quit();
    SDL_Quit();
    
    return 0;
}