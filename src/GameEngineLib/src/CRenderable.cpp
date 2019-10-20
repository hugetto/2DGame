#include "pch.h"
#include <CRenderable.h>
#include <SDL_image.h>
#include <json11/json11.hpp>
#include <fstream>
#include <streambuf>
#include <utils/Vec2.h>
#include <CGameObject.h>
#include <CCamera.h>
#include <proxy/CTextureProxy.h>
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
                    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Cannot render texture, sdl_error: %s", SDL_GetError());
                }
            }
        }
    }

    int CRenderable::Load(const json11::Json& aJSON, SDL_Renderer* aRenderer)
    {
        SDL_assert(mOwner);
        if (mOwner == nullptr)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Game Object Must be valid");
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

        bool lReferenceOk = true;
        const char* lReference = aJSON["reference"].string_value(lReferenceOk, "top_left").c_str();
        if (lReferenceOk)
        {
            if (SDL_strcasecmp(lReference, "top_left") == 0)
                mReference = EReference::E_TOP_LEFT;
            else if (SDL_strcasecmp(lReference, "top_center") == 0)
                mReference = EReference::E_TOP_CENTER;
            else if (SDL_strcasecmp(lReference, "top_right") == 0)
                mReference = EReference::E_TOP_RIGHT;
            else if (SDL_strcasecmp(lReference, "middle_left") == 0)
                mReference = EReference::E_MIDDLE_LEFT;
            else if (SDL_strcasecmp(lReference, "middle_center") == 0)
                mReference = EReference::E_MIDDLE_CENTER;
            else if (SDL_strcasecmp(lReference, "middle_right") == 0)
                mReference = EReference::E_MIDDLE_RIGHT;
            else if (SDL_strcasecmp(lReference, "bottom_left") == 0)
                mReference = EReference::E_BOTTOM_LEFT;
            else if (SDL_strcasecmp(lReference, "bottom_center") == 0)
                mReference = EReference::E_BOTTOM_CENTER;
            else if (SDL_strcasecmp(lReference, "bottom_right") == 0)
                mReference = EReference::E_BOTTOM_RIGHT;
            else
                SDL_assert(true);
        }

        if(mUnique)
        {
            SDL_Surface* lTempSurface = IMG_Load(lTextureFile);
            SDL_assert(lTempSurface);
            if (lTempSurface == 0)
            {
                SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Cannot load the image file %s, sdl_error: %s", lTextureFile, SDL_GetError());
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
                SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Cannot query the image file %s, sdl_error: %s", lTextureFile, SDL_GetError());
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
            SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Error loading image %s, sdl_error: %s", lTextureFile, SDL_GetError());
            return -1;
        }

    }
    bool CRenderable::PointInPos(const SDL_Point* aPoint) const
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
        return SDL_PointInRect(aPoint, &lPos);
    }

}