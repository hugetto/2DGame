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
#include <memory>

namespace hugGameEngine
{
    class CGameObject;
    class CSound;

    class CSoundManager {
    private:
        static CSoundManager sInstance;
        std::vector< std::unique_ptr < CSound > > mSoundList;
    public:
        CSoundManager();
        ~CSoundManager();
        CSoundManager(const CSoundManager& aGo) = delete;
        CSoundManager& operator=  (const CSoundManager&) = delete;

        inline static CSoundManager* GetInstance() { return &CSoundManager::sInstance; }

        CSound*         CreateSound(const json11::Json& aJSON, CGameObject* aGameObject, SDL_Renderer* aRenderer);
        bool            DestroySound(const CSound* aTexture);
        void            OnRender(SDL_Renderer* aRenderer) const;
    };
}

#endif