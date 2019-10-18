#include "pch.h"
#include <CSoundProxy.h>
#include <SDL_image.h>
#include <CLog.h>

namespace hugGameEngine
{
    CSoundProxy CSoundProxy::sTextureProxyInstance;

    CSoundProxy::~CSoundProxy()
    {
        for (SDL_Texture* lTexture : mTextureList)
        {
            SDL_DestroyTexture(lTexture);
        }
        mTextureList.clear();
        mTextureName.clear();
        mTextureCount.clear();
    }

    SDL_Texture* CSoundProxy::CreateTexture(const char* aTexureFile, SDL_Renderer* aRenderer)
    {
        int lFound = -1;
        for (int i = 0; i < mTextureName.size(); i++)
        {
            if (SDL_strcasecmp(mTextureName[i].c_str(), aTexureFile) == 0)
            {
                lFound = i;
                break;
            }
        }

        if (lFound >= 0)
        {
            mTextureCount[lFound]++;
            return mTextureList[lFound];
        }
        else
        {
            SDL_Surface* lTempSurface = IMG_Load(aTexureFile);
            SDL_assert(lTempSurface);
            if (lTempSurface == 0)
            {
                CLog("Cannot load the image file %s, sdl_error: %s", aTexureFile, SDL_GetError());
                return nullptr;
            }

            SDL_Texture* lTexture = SDL_CreateTextureFromSurface(aRenderer, lTempSurface);
            SDL_FreeSurface(lTempSurface);
            SDL_assert(lTexture);
            if (lTexture != 0)
            {
                mTextureList.push_back(lTexture);
                mTextureName.push_back(std::string(aTexureFile));
                mTextureCount.push_back(1);
            }
            return lTexture;
        }
    }
    void CSoundProxy::DestroyTexture(SDL_Texture* aTexture)
    {
        int lFound = -1;
        for (int i = 0; i < mTextureList.size(); i++)
        {
            if (mTextureList[i] == aTexture)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mTextureCount[lFound]--;
            if (mTextureCount[lFound] == 0)
            {
                SDL_DestroyTexture(mTextureList[lFound]);
                mTextureList.erase(mTextureList.begin() + lFound);
                mTextureName.erase(mTextureName.begin() + lFound);
                mTextureCount.erase(mTextureCount.begin() + lFound);
            }
        }
    }
    void CSoundProxy::DestroyTexture(const char* aTexureFile)
    {
        int lFound = -1;
        for (int i = 0; i < mTextureName.size(); i++)
        {
            if (SDL_strcasecmp(mTextureName[i].c_str(), aTexureFile) == 0)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mTextureCount[lFound]--;
            if (mTextureCount[lFound] == 0)
            {
                SDL_DestroyTexture(mTextureList[lFound]);
                mTextureList.erase(mTextureList.begin() + lFound);
                mTextureName.erase(mTextureName.begin() + lFound);
                mTextureCount.erase(mTextureCount.begin() + lFound);
            }
        }
    }
}