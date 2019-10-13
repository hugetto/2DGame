#include "pch.h"
#include <CApp.h>
#include <CLog.h>


namespace hugGameEngine
{
    CApp CApp::Instance;

    //==============================================================================
    CApp::CApp()
    {
    }

    //==============================================================================
    CApp::~CApp()
    {
    }

    //------------------------------------------------------------------------------
    void CApp::OnEvent(SDL_Event* Event)
    {
    }

    //------------------------------------------------------------------------------
    bool CApp::Init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            CLog("Unable to Init SDL: %s", SDL_GetError());
            return false;
        }

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            CLog("Unable to Init hinting: %s", SDL_GetError());
        }

        if ((mWindow = SDL_CreateWindow(
                "My SDL Game",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN)
                ) == NULL) 
        {
            CLog("Unable to create SDL Window: %s", SDL_GetError());
            return false;
        }

        mPrimarySurface = SDL_GetWindowSurface(mWindow);

        if ((mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL)
        {
            CLog("Unable to create renderer");
            return false;
        }

        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

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
    //Logic loop
    void CApp::Loop()
    {
    }

    //------------------------------------------------------------------------------
    //Render loop
    void CApp::Render()
    {
        SDL_RenderClear(mRenderer);
        SDL_RenderPresent(mRenderer);
    }

    //------------------------------------------------------------------------------
    void CApp::Cleanup()
    {
        if (mRenderer)
        {
            SDL_DestroyRenderer(mRenderer);
            mRenderer = NULL;
        }

        if (mWindow)
        {
            SDL_DestroyWindow(mWindow);
            mWindow = NULL;
        }

        SDLNet_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        SDL_Quit();
    }

    //------------------------------------------------------------------------------
    int CApp::Execute(int argc, char* argv[])
    {
        if (!Init()) return 0;

        SDL_Event Event;

        while (mRunning)
        {
            while (SDL_PollEvent(&Event) != 0)
            {
                OnEvent(&Event);

                if (Event.type == SDL_QUIT)
                    mRunning = false;
            }

            Loop();
            Render();

            SDL_Delay(1); // Breath
        }

        Cleanup();

        return 1;
    }

    //==============================================================================
    CApp* CApp::GetInstance() { return &CApp::Instance; }


    //==============================================================================
}
