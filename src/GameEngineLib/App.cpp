#include "pch.h"
#include <App.h>
#include <Log.h>


namespace hugGameEngine
{
    App App::Instance;

    //==============================================================================
    App::App()
    {
    }

    //------------------------------------------------------------------------------
    void App::OnEvent(SDL_Event* Event)
    {
    }

    //------------------------------------------------------------------------------
    bool App::Init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            Log("Unable to Init SDL: %s", SDL_GetError());
            return false;
        }

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            Log("Unable to Init hinting: %s", SDL_GetError());
        }

        if ((Window = SDL_CreateWindow(
                "My SDL Game",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
                ) == NULL) 
        {
            Log("Unable to create SDL Window: %s", SDL_GetError());
            return false;
        }

        PrimarySurface = SDL_GetWindowSurface(Window);

        if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
        {
            Log("Unable to create renderer");
            return false;
        }

        SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

        // load support for the JPG and PNG image formats
        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted & flags) != flags)
        {
            printf("IMG_Init: Failed to init required jpg and png support!\n");
            printf("IMG_Init: %s\n", IMG_GetError());
            return false;
        }

        if (TTF_Init() == -1)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
            return false;
        }

        if (SDLNet_Init() == -1)
        {
            printf("SDLNet_Init: %s\n", SDLNet_GetError());
            return false;
        }

        return true;
    }

    //------------------------------------------------------------------------------
    void App::Loop()
    {
    }

    //------------------------------------------------------------------------------
    void App::Render()
    {
        SDL_RenderClear(Renderer);

        SDL_RenderPresent(Renderer);
    }

    //------------------------------------------------------------------------------
    void App::Cleanup()
    {
        if (Renderer)
        {
            SDL_DestroyRenderer(Renderer);
            Renderer = NULL;
        }

        if (Window)
        {
            SDL_DestroyWindow(Window);
            Window = NULL;
        }

        SDLNet_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
    }

    //------------------------------------------------------------------------------
    int App::Execute(int argc, char* argv[])
    {
        if (!Init()) return 0;

        SDL_Event Event;

        while (Running)
        {
            while (SDL_PollEvent(&Event) != 0)
            {
                OnEvent(&Event);

                if (Event.type == SDL_QUIT)
                    Running = false;
            }

            Loop();
            Render();

            SDL_Delay(1); // Breath
        }

        Cleanup();

        return 1;
    }

    //==============================================================================
    App* App::GetInstance() { return &App::Instance; }

    int App::GetWindowWidth() { return WindowWidth; }
    int App::GetWindowHeight() { return WindowHeight; }

    //==============================================================================
}
