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
        if (mActive && mOwner->Enabled())
        {
            
            const SDL_Rect lPos = GetRectPosition();
            const SDL_Rect lWindow = CApp::GetInstance()->GetWindowRect();
            //Don't render if outside the view
            SDL_Rect lIntersect;
            if (SDL_IntersectRect(&lPos, &lWindow, &lIntersect))
            {
                if (SDL_RenderCopyEx(aRenderer, mTexture, &mSourcePos, &lPos, mOwner->GetRotationAngle(), NULL, mFlip) != 0)
                {
                    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Cannot render texture, sdl_error: %s", SDL_GetError());
                }
            }
        }
    }

    int CRenderable::Load(const json11::Json& aJSON)
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

        mName = aJSON["name"].string_value();

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

        bool lFlipOk = true;
        const char* lFlip = aJSON["flip"].string_value(lFlipOk, "SDL_FLIP_NONE").c_str();
        if (lFlipOk)
        {
            if (SDL_strcasecmp(lFlip, "SDL_FLIP_NONE") == 0)
                mFlip = SDL_FLIP_NONE;
            else if (SDL_strcasecmp(lFlip, "SDL_FLIP_HORIZONTAL") == 0)
                mFlip = SDL_FLIP_HORIZONTAL;
            else if (SDL_strcasecmp(lFlip, "SDL_FLIP_VERTICAL") == 0)
                mFlip = SDL_FLIP_VERTICAL;
            else
                SDL_assert(true);
        }

        bool lActiveOk = false;
        mActive = aJSON["active"].bool_value(lActiveOk, mActive);

        if(mUnique)
        {
            SDL_Surface* lTempSurface = IMG_Load(lTextureFile);
            SDL_assert(lTempSurface);
            if (lTempSurface == 0)
            {
                SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Cannot load the image file %s, sdl_error: %s", lTextureFile, SDL_GetError());
                return -1;
            }

            SDL_Renderer* lRenderer = CApp::GetInstance()->GetRenderer();
            SDL_Texture* lTexture = SDL_CreateTextureFromSurface(lRenderer, lTempSurface);
            SDL_FreeSurface(lTempSurface);
            SDL_assert(lTexture);
        }
        else
        {
            SDL_Renderer* lRenderer = CApp::GetInstance()->GetRenderer();
            mTexture = CTextureProxy::GetInstance()->CreateTexture(lTextureFile, lRenderer);
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
    bool CRenderable::PointInPos(const SDL_Point& aPoint) const
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
        return SDL_PointInRect(&aPoint, &lPos);
    }


    const SDL_Rect CRenderable::GetRectPosition() const
    {
        SDL_Rect lPos;
        lPos.x = mOwner->GetPosition().x;
        lPos.y = mOwner->GetPosition().y;
        lPos.w = int(mWidth * mOwner->GetScale().x);
        lPos.h = int(mHeight * mOwner->GetScale().y);

        int lWindowWidth = CApp::GetInstance()->GetWindowWidth();
        int lWindowHeight = CApp::GetInstance()->GetWindowHeight();

        if (mPosition == EPosition::E_ABSOLUTE) //Move with the camera
        {
            lPos.x += CCamera::GetInstance()->GetCameraPosition().x;
            lPos.y += CCamera::GetInstance()->GetCameraPosition().y;
        }
        else
        {
            if (mReference == EReference::E_TOP_LEFT) {}
            else if (mReference == EReference::E_TOP_CENTER)
            {
                lPos.x += static_cast<int>(lWindowWidth / 2.);
            }
            else if (mReference == EReference::E_TOP_RIGHT)
            {
                lPos.x += lWindowWidth;
            }
            else if (mReference == EReference::E_MIDDLE_LEFT)
            {
                lPos.y += static_cast<int>(lWindowHeight / 2.);
            }
            else if (mReference == EReference::E_MIDDLE_CENTER)
            {
                lPos.x += static_cast<int>(lWindowWidth / 2.);
                lPos.y += static_cast<int>(lWindowHeight / 2.);
            }
            else if (mReference == EReference::E_MIDDLE_RIGHT)
            {
                lPos.x += lWindowWidth;
                lPos.y += static_cast<int>(lWindowHeight / 2.);
            }
            else if (mReference == EReference::E_BOTTOM_LEFT)
            {
                lPos.y += lWindowHeight;
            }
            else if (mReference == EReference::E_BOTTOM_CENTER)
            {
                lPos.x += static_cast<int>(lWindowWidth / 2.);
                lPos.y += lWindowHeight;
            }
            else if (mReference == EReference::E_BOTTOM_RIGHT)
            {
                lPos.x += lWindowWidth;
                lPos.y += lWindowHeight;
            }
        }
        return lPos;
    }
}