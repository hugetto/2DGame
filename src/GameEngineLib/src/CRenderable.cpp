#include "pch.h"
#include <CLog.h>
#include <CRenderable.h>
#include <SDL_image.h>

namespace hugGameEngine
{
    CRenderable::~CRenderable()
    {

    }

    void CRenderable::Render() const
    {

    }

    int CRenderable::Load(SDL_Renderer* aRenderer, const std::string& aFilename)
    {
        mRenderer = aRenderer;
        mFileName = aFilename;

        SDL_Surface* lTempSurface = IMG_Load(aFilename.c_str());
        if (lTempSurface == 0)
        {
            CLog("Cannot load the image file %s, sdl_error: %s", aFilename.c_str(), SDL_GetError())
            return -1;
        }

        mTexture = SDL_CreateTextureFromSurface(mRenderer, lTempSurface);
        SDL_FreeSurface(lTempSurface);
        if (mTexture != 0)
        {
            if (SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight) != 0)
            {
                CLog("Cannot query the image file %s, sdl_error: %s", aFilename.c_str(), SDL_GetError());
                return -1;
            }
            return 0;
        }
        // reaching here means something went wrong
        return -1;

    }
}