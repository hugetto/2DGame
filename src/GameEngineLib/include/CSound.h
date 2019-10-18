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
#include <string>
#include <CComponent.h>

class Mix_Chunk;

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
        std::vector< std::pair<int, std::string> >  mPlayingChunksChannel;
        bool                                        mLoop = false;
    public:
                CSound      (CGameObject* aOwner) : CComponent(aOwner) { mComponentType = CComponent::EComponentType::E_Sound; }
               ~CSound      ();
                CSound      (const CSound& aGo) = delete;
        CSound& operator=   (const CSound&)     = delete;
        bool    Load        (const json11::Json& aJSON, const CGameObject* aGameObject);
        bool    PlaySound   (const char* aMusicName);
        bool    PlayMusic   (const char* aSoundName);
        bool    PauseSound  (const char* aSoundName);
        bool    PauseMusic  (const char* aMusicName);
        bool    StopSound   (const char* aSoundName);
        bool    StopMusic   (const char* aMusicName);
    };
}
#endif
