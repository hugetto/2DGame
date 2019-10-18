//==============================================================================
/*
    Sound Manager
    Hug Beneit
*/
//==============================================================================
#ifndef __CSOUNDMANAGER_H__
#define __CSOUNDMANAGER_H__

#include <json11/json11.hpp>
#include <SDL.h>
#include <vector>

namespace hugGameEngine
{
    class CGameObject;
    class CSound;

    class CSoundManager {
    private:
        static CSoundManager sInstance;
        std::vector< CSound* > mChunkList;
    public:
        CSoundManager();
        ~CSoundManager();
        CSoundManager(const CSoundManager& aGo) = delete;
        CSoundManager& operator=  (const CSoundManager&) = delete;

        inline static CSoundManager* GetInstance() { return &CSoundManager::sInstance; }

        CSound*         CreateSound(const json11::Json& aJSON, CGameObject* aGameObject);
        bool            DestroySound(const CSound* aTexture);
        void            OnRender(SDL_Renderer* aRenderer) const;
    };
}

#endif