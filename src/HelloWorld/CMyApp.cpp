
#include "pch.h"
#include "CMyApp.h"
#include <CApp.h>
#include <json11/json11.hpp>
#include <string>
#include <fstream>
#include <streambuf>
#include <CGameObjectManager.h>
#include <CGameObject.h>
#include <CTextureManager.h>
#include <CSoundManager.h>
#include <CScript.h>
#include <CScriptManager.h>
#include <CLog.h>
#include <algorithm>
#include "AllScripts.inc"
#include "SMainController.h"

#define MAIN_SCENE "./datasource/scenes/main/main.scene"

using namespace hugGameEngine;

namespace MyGame {

    CMyApp CMyApp::sInstance;
    CMyApp* CMyApp::GetInstance()
    {
        return &sInstance;
    }

    int CMyApp::Execute(int argc, char* argv[])
    {
        mCApp = new CApp();
        if (!Init())
            return 0;

        SDL_Event lEvent;

        //FPS limiter
        Uint32   lInitTime = 0;
        Uint32   lEndTime = 0;
        Uint32  lDelay = 0;
        while (mRunning)
        {
            lInitTime = SDL_GetTicks();
            while (SDL_PollEvent(&lEvent) != 0)
            {
                OnEvent(&lEvent);

                if (lEvent.type == SDL_QUIT)
                    mRunning = false;
            }

            Loop(lDelay + static_cast<Uint32>(mCApp->GetFPSLimit()));
            Render();

            lEndTime = SDL_GetTicks();
            lDelay = static_cast<Uint32>(std::max(mCApp->GetFPSLimit() - (lEndTime - lInitTime), 0.f));
            SDL_Delay(lDelay);
        }

        Cleanup();

        return 1;
    }

    void CMyApp::OnEvent(SDL_Event* aEvent)
    {
        mCApp->OnEvent(aEvent);
    }

    bool CMyApp::Init()
    {
        bool lOk = mCApp->Init();

        //Load main scene config file
        lOk = lOk && CreateObject(MAIN_SCENE);
        return lOk;
    }

    void CMyApp::Loop(Uint32 aRenderTime)
    {
        mCApp->Loop(aRenderTime);
    }

    void CMyApp::Render()
    {
        mCApp->Render();
    }

    void CMyApp::Cleanup()
    {
        mCApp->Cleanup();
    }

    bool CMyApp::CreateObject(const char* aFileName)
    {
        bool lOk = false;
        std::ifstream lMainScene(aFileName);
        if (lMainScene.fail())
        {
            CLog("Failed loading scene %s", aFileName);
            return false;
        }
        std::string lMainCfgStr((std::istreambuf_iterator<char>(lMainScene)), std::istreambuf_iterator<char>());
        std::string lError;
        const json11::Json lJSON = json11::Json::parse(lMainCfgStr, lError);
        if (!lError.empty())
        {
            CLog("JSON parse error %s", lError.c_str());
            SDL_assert(false);
            return false;
        }
        for (json11::Json lItem : lJSON.array_items(lOk))
        {
            if (SDL_strcasecmp(lItem["type"].string_value(lOk).c_str(), "gameobject") == 0)
            {
                CGameObject* lGameObject = CGameObjectManager::GetInstance()->CreateGameObject(lItem);
                SDL_assert(lGameObject);
            }
        }
        for (json11::Json lItem : lJSON.array_items(lOk))
        {
            if (SDL_strcasecmp(lItem["type"].string_value(lOk).c_str(), "renderable") == 0)
            {
                CGameObject* lGO = CGameObjectManager::GetInstance()->FindGameObject(lItem["name"].string_value(lOk).c_str());
                SDL_assert(lGO);
                CRenderable* lTexture = CTextureManager::GetInstance()->CreateTexture(lItem, lGO, mCApp->GetRenderer());
                lGO->AddComponent((CComponent*)lTexture);
                SDL_assert(lTexture);
            }
        }
        for (json11::Json lItem : lJSON.array_items(lOk))
        {
            if (SDL_strcasecmp(lItem["type"].string_value(lOk).c_str(), "script") == 0)
            {
                CGameObject* lGO = CGameObjectManager::GetInstance()->FindGameObject(lItem["name"].string_value(lOk).c_str());
                SDL_assert(lGO);

                bool lOk = false;
                const char* lFileName = lItem["script_name"].string_value(lOk, "").c_str();
                CScript* lNewScript = nullptr;
                if (lOk)
                {
                    if (SDL_strcasecmp(lFileName, "SMainController") == 0)
                        lNewScript = new SMainController(lGO, lItem);
                }
                SDL_assert(lNewScript);
                CScriptManager::GetInstance()->RegisterScript(lNewScript);
            }
        }
        for (json11::Json lItem : lJSON.array_items(lOk))
        {
            if (SDL_strcasecmp(lItem["type"].string_value(lOk).c_str(), "sound") == 0)
            {
                CGameObject* lGO = CGameObjectManager::GetInstance()->FindGameObject(lItem["name"].string_value(lOk).c_str());
                SDL_assert(lGO);
                CSound* lSound = CSoundManager::GetInstance()->CreateSound(lItem, lGO);
                SDL_assert(lSound);
            }
        }
        return lOk;
    }
}
