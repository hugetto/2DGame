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
#include <SDL_mixer.h>
#include <vector>

namespace hugGameEngine
{
    class CGameObject;
    class CSound;

    class CSoundManager {
    private:
        static CSoundManager    sSoundManagerInstance;
        std::vector< CSound* >  mChunkList;
        int                     mGlobalVolume   = MIX_MAX_VOLUME;
        int                     mMusicVolume    = MIX_MAX_VOLUME;
        int                     mChunksVolume   = MIX_MAX_VOLUME;
    public:
        CSoundManager   ();
        ~CSoundManager  ();
        CSoundManager(const CSoundManager& aGo) = delete;
        CSoundManager& operator=  (const CSoundManager&) = delete;

        CSound*                 CreateSound     (const json11::Json& aJSON, CGameObject* aGameObject);
        bool                    DestroySound    (const CSound* aTexture);
        static CSoundManager*   GetInstance() { return &CSoundManager::sSoundManagerInstance; }
    };
}

#endif