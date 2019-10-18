#include "pch.h"
#include <CSound.h>
#include <CGameObject.h>
#include <CLog.h>

namespace hugGameEngine
{
    CSound::~CSound()
    {
        for (std::vector< Mix_Music* >::iterator lIt = mMusicList.begin(); lIt != mMusicList.end(); lIt++)
        {
            Mix_FreeMusic(*lIt);
        }
        mMusicList.clear();
        for (std::vector< Mix_Chunk* >::iterator lIt = mSoundList.begin(); lIt != mSoundList.end(); lIt++)
        {
            Mix_FreeChunk(*lIt);
        }
        mSoundList.clear();
    }

    CSound* CSound::Load(const json11::Json& aJSON, const CGameObject* aGameObject, SDL_Renderer* aRenderer)
    {
        bool lOk = false;
        const char* lFileName = aJSON["type"].string_value(lOk).c_str();
        if (SDL_strcasecmp(aJSON["type"].string_value(lOk).c_str(), "music") == 0)
        {
            Mix_Music* lMusic = Mix_LoadMUS(lFileName);
            SDL_assert(lMusic);
            if (lMusic == NULL)
            {
                CLog("Error loading music file %s, SDL error %s", lFileName, Mix_GetError());
                return nullptr;
            }
            mMusicList.push_back(lMusic);
        }
        else
        {
            Mix_Chunk* lSound = Mix_LoadWAV(lFileName);
            //SDL_assert(lSound);
            if (lSound == NULL)
            {
                CLog("Error loading sound file %s, SDL error %s", lFileName, Mix_GetError());
                return nullptr;
            }
            mSoundList.push_back(lSound);
        }
        return nullptr;
    }

    bool CSound::PlaySound(const char* aSoundName)
    {
        return true;
    }

    bool CSound::PlayMusic(const char* aSoundName)
    {
        return true;
    }

    bool CSound::PauseSound(const char* aSoundName)
    {
        return true;
    }

    bool CSound::PauseMusic(const char* aSoundName)
    {
        return true;
    }

    bool CSound::StopSound(const char* aSoundName)
    {
        return true;
    }

    bool CSound::StopMusic(const char* aSoundName)
    {
        return true;
    }
}