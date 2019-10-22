//==============================================================================
/*
    
    Hug Beneit
*/
//==============================================================================
#ifndef __CSCRIPTMANAGER_H__
#define __CSCRIPTMANAGER_H__

#include <json11/json11.hpp>
#include <SDL.h>
#include <vector>
#include <memory>

namespace hugGameEngine
{
    class CGameObject;
    class CScript;

    class CScriptManager {
    private:
        static CScriptManager sInstance;
        std::vector< CScript* > mScriptList;
    public:
        CScriptManager             ();
        ~CScriptManager            ();
        CScriptManager             (const CScriptManager& aGo) = delete;
        CScriptManager& operator=  (const CScriptManager&) = delete;

        inline static CScriptManager* GetInstance() { return &CScriptManager::sInstance; }

        void                    RegisterScript      (CScript* aScript);
        bool                    DestroyScript       (const CScript* aScript);
        void                    Loop                (Uint32 aRenterTime);
        void                    OnEvent             (const SDL_Event* aEvent);
        CScript*                FindScripByName     (const char* aScriptType);
        std::vector< CScript* > FindAllScripByName  (const char* aScriptType);
    };
}

#endif