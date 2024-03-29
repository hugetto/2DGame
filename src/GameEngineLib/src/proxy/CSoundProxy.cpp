#include "pch.h"
#include <proxy/CSoundProxy.h>
#include <SDL_image.h>

namespace hugGameEngine
{
    CSoundProxy CSoundProxy::sSoundProxyInstance;

    CSoundProxy::~CSoundProxy()
    {
        for (std::vector< Mix_Music* >::iterator lIt = mMusicList.begin(); lIt != mMusicList.end(); lIt++)
        {
            Mix_FreeMusic(*lIt);
        }
        for (std::vector< Mix_Chunk* >::iterator lIt = mChunkList.begin(); lIt != mChunkList.end(); lIt++)
        {
            Mix_FreeChunk(*lIt);
        }
        mMusicList.clear();
        mMusicName.clear();
        mMusicCount.clear();

        mChunkList.clear();
        mChunkName.clear();
        mChunkCount.clear();
    }

    Mix_Music* CSoundProxy::CreateMusic(const char* aMusicFile)
    {
        int lFound = -1;
        for (size_t i = 0; i < mMusicName.size(); i++)
        {
            if (SDL_strcasecmp(mMusicName[i].c_str(), aMusicFile) == 0)
            {
                lFound = i;
                break;
            }
        }

        if (lFound >= 0)
        {
            mMusicCount[lFound]++;
            return mMusicList[lFound];
        }
        else
        {
            Mix_Music* lMusic = Mix_LoadMUS(aMusicFile);
            SDL_assert(lMusic);
            if (lMusic == NULL)
            {
                SDL_LogDebug(SDL_LOG_CATEGORY_AUDIO, "Error loading music file %s, SDL error %s", aMusicFile, Mix_GetError());
                return nullptr;
            }
            mMusicList.push_back(lMusic);
            mMusicName.push_back(std::string(aMusicFile));
            mMusicCount.push_back(1);

            return lMusic;
        }
    }

    Mix_Chunk* CSoundProxy::CreateChunk(const char* aChunkFile)
    {
        int lFound = -1;
        for (size_t i = 0; i < mChunkName.size(); i++)
        {
            if (SDL_strcasecmp(mChunkName[i].c_str(), aChunkFile) == 0)
            {
                lFound = i;
                break;
            }
        }

        if (lFound >= 0)
        {
            mChunkCount[lFound]++;
            return mChunkList[lFound];
        }
        else
        {
            Mix_Chunk* lChunk = Mix_LoadWAV(aChunkFile);
            SDL_assert(lChunk);
            if (lChunk == NULL)
            {
                SDL_LogDebug(SDL_LOG_CATEGORY_AUDIO, "Error loading Chunk file %s, SDL error %s", aChunkFile, Mix_GetError());
                return nullptr;
            }
            mChunkList.push_back(lChunk);
            mChunkName.push_back(std::string(aChunkFile));
            mChunkCount.push_back(1);

            return lChunk;
        }
    }

    bool CSoundProxy::DestroyMusic(Mix_Music* aMusic)
    {
        int lFound = -1;
        for (size_t i = 0; i < mMusicList.size(); i++)
        {
            if (mMusicList[i] == aMusic)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mMusicCount[lFound]--;
            if (mMusicCount[lFound] == 0)
            {
                Mix_FreeMusic(mMusicList[lFound]);
                mMusicList.erase(mMusicList.begin() + lFound);
                mMusicName.erase(mMusicName.begin() + lFound);
                mMusicCount.erase(mMusicCount.begin() + lFound);
            }
            return true;
        }
        return false;
    }

    bool CSoundProxy::DestroyChunk(Mix_Chunk* aChunk)
    {
        int lFound = -1;
        for (size_t i = 0; i < mChunkList.size(); i++)
        {
            if (mChunkList[i] == aChunk)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mChunkCount[lFound]--;
            if (mChunkCount[lFound] == 0)
            {
                Mix_FreeChunk(mChunkList[lFound]);
                mChunkList.erase(mChunkList.begin() + lFound);
                mChunkName.erase(mChunkName.begin() + lFound);
                mChunkCount.erase(mChunkCount.begin() + lFound);
            }
            return true;
        }
        return false;
    }
}