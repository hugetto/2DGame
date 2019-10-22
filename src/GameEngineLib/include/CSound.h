//==============================================================================
/*
    Base Sound Object
    Hug Beneit
*/
//==============================================================================
#ifndef __CSOUND_H__
#define __CSOUND_H__

#include <json11/json11.hpp>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include <string>
#include <CComponent.h>

namespace hugGameEngine
{
    class CGameObject;
    class CSound : public CComponent
    {
    private:
        std::vector< Mix_Music* >                   mMusicList;
        std::vector< Mix_Chunk* >                   mChunkList;
        std::vector< std::string >                  mMusicNameList;
        std::vector< std::string >                  mChunkNameList;
        std::map< Mix_Chunk*, int >                 mPlayingChunksChannel;
        bool                                        mLoop = false;
        int                                         mVolume = MIX_MAX_VOLUME;
    public:
                CSound      (CGameObject* aOwner) : CComponent(aOwner) { mComponentType = CComponent::EComponentType::E_Sound; }
               ~CSound      ();
                CSound      (const CSound& aGo) = delete;
        CSound& operator=   (const CSound&)     = delete;
        bool    Load        (const json11::Json& aJSON, const CGameObject* aGameObject);
        bool    PlayChunk   (const char* aMusicName);
        bool    PlayMusic   (const char* aSoundName);
        bool    PauseChunk  (const char* aSoundName);
        bool    PauseMusic  (const char* aMusicName);
        bool    ResumeChunk (const char* aSoundName);
        bool    ResumeMusic (const char* aMusicName);
        void    SetVolume   (int aVolume);
        bool    HasSound    (const char* aSoundName);
    };
}
#endif
