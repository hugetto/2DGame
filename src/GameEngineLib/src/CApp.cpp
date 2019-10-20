#include "pch.h"
#include <CApp.h>
#include <managers/CTextureManager.h>
#include <managers/CGameObjectManager.h>
#include <managers/CScriptManager.h>
#include <json11/json11.hpp>
#include <string>
#include <fstream>
#include <streambuf>

#define MAIN_CFG "./datasource/config/main.cfg"

namespace hugGameEngine
{
    CApp CApp::sInstance;
    CApp* CApp::GetInstance()
    {
        return &sInstance;
    }
    //==============================================================================
    CApp::CApp()
    {
    }

    //==============================================================================
    CApp::~CApp()
    {
    }

    //------------------------------------------------------------------------------
    void CApp::OnEvent(const SDL_Event* aEvent)
    {
        CScriptManager::GetInstance()->OnEvent(aEvent);
    }

    //------------------------------------------------------------------------------
    bool CApp::Init()
    {
        //Read Main Configuration File
        std::ifstream lMainCfg(MAIN_CFG);
        std::string lMainCfgStr ((std::istreambuf_iterator<char>(lMainCfg)), std::istreambuf_iterator<char>());
        std::string lError;
        //Parse configuration file as JSON
        const json11::Json lJSON = json11::Json::parse(lMainCfgStr, lError);

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to Init SDL: %s", SDL_GetError());
            return false;
        }

        bool lOk = false;
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, lJSON["render_quality"].string_value(lOk, "1").c_str()))
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to Init hinting: %s", SDL_GetError());
        }

        mWindowWidth = lJSON["window_width"].int_value(lOk, 1024);
        mWindowHeight = lJSON["window_height"].int_value(lOk, 640);
        if ((mWindow = SDL_CreateWindow(
            lJSON["game_name"].string_value(lOk, "error setting game name").c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN)
            ) == NULL) 
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to create SDL Window: %s", SDL_GetError());
            return false;
        }

        mPrimarySurface = SDL_GetWindowSurface(mWindow);

        if ((mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to create renderer");
            return false;
        }

        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

        // load support for the JPG and PNG image formats
        int lFlags = IMG_INIT_JPG | IMG_INIT_PNG;
        int lInitted = IMG_Init(lFlags);
        if ((lInitted & lFlags) != lFlags)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init: Failed to init required jpg and png support!\n");
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init: %s\n", IMG_GetError());
            return false;
        }

        if (TTF_Init() == -1)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init: %s\n", TTF_GetError());
            return false;
        }

        if (Mix_OpenAudio(lJSON["frequency"].int_value(lOk, 22050), MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio: %s\n", Mix_GetError());
            return false;
        }

        if (SDLNet_Init() == -1)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDLNet_Init: %s\n", SDLNet_GetError());
            return false;
        }

        if (lJSON["limit_fps"].is_number())
        {
            int lFps = lJSON["limit_fps"].int_value(lOk, 30);
            SDL_assert(lFps > 0);
            mFPSLimit = 1000.f/ lFps;
        }

        return lOk;
    }

    //------------------------------------------------------------------------------
    //Logic loop
    void CApp::Loop(Uint32 aRenderTime)
    {
        CGameObjectManager::GetInstance()->Loop(aRenderTime);
        CScriptManager::GetInstance()->Loop(aRenderTime);
    }

    //------------------------------------------------------------------------------
    //Render loop
    void CApp::Render()
    {
        if (SDL_RenderClear(mRenderer) != 0)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to Render SDL: %s", SDL_GetError());
        }
        CTextureManager::GetInstance()->OnRender(mRenderer);
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
}
