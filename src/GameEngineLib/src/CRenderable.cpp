#include "pch.h"
#include <CLog.h>
#include <CRenderable.h>
#include <SDL_image.h>
#include <json11/json11.hpp>
#include <fstream>
#include <streambuf>
#include <Vec2.h>
#include <CGameObject.h>
#include <CCamera.h>
#include <CTextureProxy.h>
#include <CApp.h>

namespace hugGameEngine
{
    CRenderable::~CRenderable()
    {
        if (mUnique)
        {
            SDL_DestroyTexture(mTexture);
        }
        else
        {
            CTextureProxy::GetInstance()->DestroyTexture(mTexture);
        }
    }

    void CRenderable::OnRender(SDL_Renderer* aRenderer) const
    {
        if (mOwner->Enabled())
        {
            SDL_Rect lPos;
            lPos.x = mOwner->GetPosition().x;
            lPos.y = mOwner->GetPosition().y;
            lPos.w = int(mWidth * mOwner->GetScale().x);
            lPos.h = int(mHeight * mOwner->GetScale().y);

            if (mPosition == EPosition::E_ABSOLUTE) //Move with the camera
            {
                lPos.x += CCamera::GetInstance()->GetCameraPosition().x;
                lPos.y += CCamera::GetInstance()->GetCameraPosition().y;
            }

            //Don't render if outside the view
            //if (((lPos.x + lPos.w >= 0) && (lPos.x < CApp::GetInstance()->GetWindowWidth())) &&
            //    ((lPos.y + lPos.h >= 0) && (lPos.y < CApp::GetInstance()->GetWindowHeight())))
            {
                if (SDL_RenderCopyEx(aRenderer, mTexture, &mSourcePos, &lPos, mOwner->GetRotationAngle(), NULL, mFlip) != 0)
                {
                    CLog("Cannot render texture, sdl_error: %s", SDL_GetError());
                }
            }
        }
    }

    int CRenderable::Load(const json11::Json& aJSON, SDL_Renderer* aRenderer)
    {
        SDL_assert(mOwner);
        if (mOwner == nullptr)
        {
            CLog("Game Object Must be valid");
            return -1;
        }

        bool lOk = false;

        if (SDL_strcasecmp(aJSON["camera_position"].string_value(lOk, "absolute").c_str(), "fixed") == 0)
            mPosition = EPosition::E_FIXED;
        else
            mPosition = EPosition::E_ABSOLUTE;

        const char* lTextureFile = aJSON["texture_file"].string_value(lOk, "").c_str();
        mUnique = aJSON["unique"].bool_value(lOk, false);
        mLayer = aJSON["layer"].int_value(lOk, 0);

        if(mUnique)
        {
            SDL_Surface* lTempSurface = IMG_Load(lTextureFile);
            SDL_assert(lTempSurface);
            if (lTempSurface == 0)
            {
                CLog("Cannot load the image file %s, sdl_error: %s", lTextureFile, SDL_GetError());
                return -1;
            }

            SDL_Texture* lTexture = SDL_CreateTextureFromSurface(aRenderer, lTempSurface);
            SDL_FreeSurface(lTempSurface);
            SDL_assert(lTexture);
        }
        else
        {
            mTexture = CTextureProxy::GetInstance()->CreateTexture(lTextureFile, aRenderer);
        }
        if (mTexture != 0)
        {
            if (SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight) != 0)
            {
                CLog("Cannot query the image file %s, sdl_error: %s", lTextureFile, SDL_GetError());
                return -1;
            }
            mSourcePos.x = 0;
            mSourcePos.y = 0;
            mSourcePos.w = mWidth;
            mSourcePos.h = mHeight;
            return 0;
        }
        else
        {
            CLog("Error loading image %s, sdl_error: %s", lTextureFile, SDL_GetError());
            return -1;
        }

    }
}