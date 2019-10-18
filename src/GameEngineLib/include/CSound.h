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

class Mix_Chunk;

namespace hugGameEngine
{
    class CGameObject;
    class CSound
    {
    private:
        std::vector< Mix_Music* >   mMusicList;
        std::vector< Mix_Chunk* >   mSoundList;
        std::vector< std::string >  mMusicNameList;
        std::vector< std::string >  mSoundNameList;
        bool                        mLoop = false;
    public:
                CSound      () {}
               ~CSound      ();
                CSound      (const CSound& aGo) = delete;
        CSound& operator=   (const CSound&)     = delete;
        CSound* Load        (const json11::Json& aJSON, const CGameObject* aGameObject, SDL_Renderer* aRenderer);
        bool    PlaySound   (const char* aSoundName);
        bool    PlayMusic   (const char* aSoundName);
        bool    PauseSound  (const char* aSoundName);
        bool    PauseMusic  (const char* aSoundName);
        bool    StopSound   (const char* aSoundName);
        bool    StopMusic   (const char* aSoundName);
    };
}
#endif
