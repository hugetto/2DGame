//==============================================================================
/*
    Stores all the textures and render them in a ordered way
    Hug Beneit
*/
//==============================================================================
#ifndef __CGAMEOBJECTMANAGER_H__
#define __CGAMEOBJECTMANAGER_H__

#include <json11/json11.hpp>
#include <SDL.h>
#include <vector>
#include <memory>

namespace hugGameEngine
{
    class CGameObject;

    class CGameObjectManager {
    private:
        static CGameObjectManager sInstance;
        std::vector< std::unique_ptr < CGameObject > > mGameObjectList;
    public:
        CGameObjectManager             ();
        ~CGameObjectManager            ();
        CGameObjectManager             (const CGameObjectManager& aGo) = delete;
        CGameObjectManager& operator=  (const CGameObjectManager&) = delete;

        inline static CGameObjectManager* GetInstance() { return &CGameObjectManager::sInstance; }

        CGameObject*    CreateGameObject    (const json11::Json& aJSON);
        bool            DestroyGameObject   (const CGameObject* aGameObject);
        void            Loop                (unsigned int aRenderTime);
        CGameObject*    FindGameObject      (const char* aGameObjectName);
    };
}

#endif