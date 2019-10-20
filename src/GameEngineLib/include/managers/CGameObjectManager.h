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

namespace hugGameEngine
{
    class CGameObject;

    class CGameObjectManager {
    private:
        static CGameObjectManager sInstance;
        std::vector< CGameObject* > mGameObjectList;
    public:
        CGameObjectManager             ();
        ~CGameObjectManager            ();
        CGameObjectManager             (const CGameObjectManager& aGo) = delete;
        CGameObjectManager& operator=  (const CGameObjectManager&) = delete;

        inline static CGameObjectManager* GetInstance() { return &CGameObjectManager::sInstance; }

        CGameObject*                    CreateGameObject    (const json11::Json& aJSON);
        bool                            DestroyGameObject   (const CGameObject* aGameObject);
        void                            Loop                (Uint32 aRenderTime)      const;
        CGameObject*                    FindGameObject      (const char* aGameObjectName)   const;
        std::vector< CGameObject* >     FindAllGameObjects  (const char* aGameObjectName)   const;
        std::vector< CGameObject* >     GetGameObjectInPos  (const SDL_Point& aPosition)    const;
    };
}

#endif