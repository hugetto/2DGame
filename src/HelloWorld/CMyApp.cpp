
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
#include "AllScripts.inc"
#include "SMainController.h"

#define MAIN_SCENE "./datasource/scenes/main/main.scene"

using namespace hugGameEngine;

namespace MyGame {
    CMyApp CMyApp::Instance;

    int CMyApp::Execute(int argc, char* argv[])
    {
        int lOk = CApp::Execute(argc, argv);
        return lOk;
    }

    void CMyApp::OnEvent(SDL_Event* aEvent)
    {
        CApp::OnEvent(aEvent);
    }

    bool CMyApp::Init()
    {
        bool lOk = CApp::Init();

        //Load main scene config file
        lOk = lOk && CreateObject(MAIN_SCENE);
        return lOk;
    }

    void CMyApp::Loop(unsigned int aRenderTime)
    {
        CApp::Loop(aRenderTime);
    }

    void CMyApp::Render()
    {
        CApp::Render();
    }

    void CMyApp::Cleanup()
    {
        CApp::Cleanup();
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
            CLog("JSON parse error %s", lError);
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
                CRenderable* lTexture = CTextureManager::GetInstance()->CreateTexture(lItem, lGO, mRenderer);
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
                    if (SDL_strcasecmp(lFileName, SMainController::GetScriptName()) == 0)
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
                CSound* lSound = CSoundManager::GetInstance()->CreateSound(lItem, lGO, mRenderer);
                SDL_assert(lSound);
            }
        }
        return lOk;
    }

    CMyApp* CMyApp::GetInstance() { return &CMyApp::Instance; }
}
