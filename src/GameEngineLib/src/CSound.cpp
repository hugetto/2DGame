#include "pch.h"
#include <CSound.h>
#include <CGameObject.h>
#include <utils/CLog.h>
#include <proxy/CSoundProxy.h>

namespace hugGameEngine
{
    CSound::~CSound()
    {
        for (Mix_Music* lMusic : mMusicList)
        {
            CSoundProxy::GetInstance()->DestroyMusic(lMusic);
        }
        mMusicList.clear();
        for (Mix_Chunk* lChunk : mChunkList)
        {
            CSoundProxy::GetInstance()->DestroyChunk(lChunk);
        }
        mChunkList.clear();
        mPlayingChunksChannel.clear();
    }

    bool CSound::Load(const json11::Json& aJSON, const CGameObject* aGameObject)
    {
        bool lOk = false;

        const json11::Json& lSoundRes = aJSON["sound_list"];
        for (const json11::Json& lItem : lSoundRes.array_items(lOk))
        {
            const char* lFileName = lItem["filename"].string_value(lOk).c_str();
            const char* lSoundName = lItem["sound_name"].string_value(lOk).c_str();
            if (lOk && SDL_strcasecmp(lItem["type"].string_value(lOk).c_str(), "music") == 0)
            {
                Mix_Music* lMusic = CSoundProxy::GetInstance()->CreateMusic(lFileName);
                SDL_assert(lMusic);

                //Prevent adding duplicated sounds
                bool lFound = false;
                for (std::string lName : mMusicNameList)
                {
                    lFound = SDL_strcasecmp(lName.c_str(), lSoundName) == 0;
                }
                SDL_assert(!lFound); //Duplicated Music audio. check your configuration file please
                if (!lFound)
                {
                    mMusicList.push_back(lMusic);
                    mMusicNameList.push_back(lSoundName);
                }
            }
            else if (lOk && SDL_strcasecmp(lItem["type"].string_value(lOk).c_str(), "chunk") == 0)
            {
                Mix_Chunk* lSound = CSoundProxy::GetInstance()->CreateChunk(lFileName);
                SDL_assert(lSound);
                //Prevent adding duplicated sounds
                bool lFound = false;
                for (std::string lName : mChunkNameList)
                {
                    lFound = SDL_strcasecmp(lName.c_str(), lSoundName) == 0;
                }
                SDL_assert(!lFound); //Duplicated Chunk audio. check your configuration file please
                if (!lFound)
                {
                    mChunkList.push_back(lSound);
                    mChunkNameList.push_back(lSoundName);
                }
            }
            else
            {
                SDL_assert(false);
            }
            mVolume = lItem["volume"].int_value(mVolume);
            mLoop = lItem["loop"].bool_value();
        }
        
        return lOk;
    }

    bool CSound::PlayChunk(const char* aSoundName)
    {
        size_t i = 0;
        bool lFound = false;
        for (i = 0; i < mChunkNameList.size(); ++i)
        {
            if (SDL_strcasecmp(mChunkNameList[i].c_str(), aSoundName) == 0)
            {
                lFound = true;
                break;
            }
        }
        if (lFound)
        {
            if (Mix_Playing(-1) == 0)
            {
                //Play the music
                int lChannel = Mix_PlayChannel(-1, mChunkList[i], mLoop ? -1 : 0);
                if(lChannel == -1)
                {
                    CLog("Mix_PlayChannel: %s\n", Mix_GetError());
                    SDL_assert(false);
                    return false;
                }
                mPlayingChunksChannel[mChunkList[i]] = lChannel;
                Mix_VolumeChunk(mChunkList[i], mVolume);
            }
            else
            {
                CLog("Mix_Playing: %s\n", Mix_GetError());
                SDL_assert(false);
            }
        }
        return lFound;
    }

    bool CSound::PlayMusic(const char* aMusicName)
    {
        size_t i = 0;
        bool lFound = false;
        for (i = 0; i < mMusicNameList.size(); ++i)
        {
            if (SDL_strcasecmp(mMusicNameList[i].c_str(), aMusicName) == 0)
            {
                lFound = true;
                break;
            }
        }
        if (lFound)
        {
            if (Mix_PlayingMusic() == 0)
            {
                //Play the music
                if (Mix_PlayMusic(mMusicList[i], mLoop ? -1 : 1) == -1)
                {
                    CLog("Mix_PlayMusic: %s\n", Mix_GetError());
                    SDL_assert(false);
                    return false;
                }
                Mix_VolumeMusic(mVolume);
            }
            else
            {
                CLog("Mix_PlayingMusic: %s\n", Mix_GetError());
            }
        }
        return lFound;
    }

    bool CSound::PauseChunk(const char* aSoundName)
    {
        size_t i = 0;
        bool lFound = false;
        for (i = 0; i < mMusicNameList.size(); ++i)
        {
            if (SDL_strcasecmp(mMusicNameList[i].c_str(), aSoundName) == 0)
            {
                lFound = true;
                break;
            }
        }
        if (lFound)
        {
            if (Mix_Playing(mPlayingChunksChannel[mChunkList[lFound]]) == 0)
            {
                Mix_Pause(mPlayingChunksChannel[mChunkList[lFound]]);
            }
            else
            {
                CLog("Mix_Playing: %s\n", Mix_GetError());
            }
        }
        else
        {
            CLog("Sound not found %s", aSoundName);
        }
        return lFound;
    }

    bool CSound::PauseMusic(const char* aMusicName)
    {
        size_t i = 0;
        bool lFound = false;
        for (i = 0; i < mMusicNameList.size(); ++i)
        {
            if (SDL_strcasecmp(mMusicNameList[i].c_str(), aMusicName) == 0)
            {
                lFound = true;
                break;
            }
        }
        if (lFound)
        {
            if (Mix_PlayingMusic() == 0)
            {
                //Play the music
                if (Mix_PausedMusic() == -1)
                {
                    CLog("Mix_PausedMusic: %s\n", Mix_GetError());
                    SDL_assert(false);
                    return false;
                }
            }
            else
            {
                CLog("Mix_PlayingMusic: %s\n", Mix_GetError());
            }
        }
        else
        {
            CLog("Music not found %s", aMusicName);
        }
        return lFound;
    }

    bool CSound::ResumeChunk(const char* aSoundName)
    {
        return true;
    }

    bool CSound::ResumeMusic(const char* aMusicName)
    {
        size_t i = 0;
        bool lFound = false;
        for (i = 0; i < mMusicNameList.size(); ++i)
        {
            if (SDL_strcasecmp(mMusicNameList[i].c_str(), aMusicName) == 0)
            {
                lFound = true;
                break;
            }
        }
        if (lFound)
        {
            if (Mix_PlayingMusic() == 0)
            {
                //Play the music
                Mix_ResumeMusic();
            }
            else
            {
                CLog("Mix_PlayingMusic: %s\n", Mix_GetError());
            }
        }
        else
        {
            CLog("Music not found %s", aMusicName);
        }
        return lFound;
    }

    void CSound::SetVolume(int aVolume)
    {
        mVolume = aVolume;
    }
}