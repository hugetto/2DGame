#include "SPieceController.h"
#include <managers/CGameObjectManager.h>
#include <managers/CTextureManager.h>
#include <managers/CScriptManager.h>
#include <CGameObject.h>
#include <utils/Vec2.h>
#include <CRenderable.h>
#include <CSound.h>
#include <math.h>
#include <algorithm>

#define PIECE_CFG "./datasource/prefabs/pieces.prefab"

using namespace hugGameEngine;

namespace MyGame {

    SPieceController::SPieceController(hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON) : 
        CScript(aOwner, aJSON)
    {
        mScriptName = "SPieceController";
    }

    SPieceController::~SPieceController()
    {

    }
    void SPieceController::OnCreate()
    {
    }
    void SPieceController::OnEnable()
    {
        CComponent* lRenderer = mOwner->FindFirstComponent(CComponent::EComponentType::E_Renderable);
        SDL_assert(lRenderer);
        Vec2i lPos(mPieceLogicPositionX * static_cast<CRenderable*>(lRenderer)->GetWidth(), mPieceLogicPositionY* static_cast<CRenderable*>(lRenderer)->GetHeight());
        mOwner->SetPosition(lPos);
    }
    void SPieceController::OnDisable()
    {
    }
    void SPieceController::OnDestroy()
    {
    }
    void SPieceController::Loop(Uint32 aRenderTime)
    {
        if (mSelected)
        {
            Vec2i lTmp;
            if (SDL_GetMouseState(&lTmp.x, &lTmp.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                //Check max position allowed
                int lMaxAllowed = 0;
                int lMinAllowed = 0;

                if (mDirection == EMoveDirection::E_HORIZONTAL)
                {
                    lMinAllowed = mInitialMousePosition.y - 128;
                    lMaxAllowed = mInitialMousePosition.y + 128;
                    lTmp.x = mInitialMousePosition.x;
                    if (mInitialMousePosition.y > lTmp.y)
                    {
                        lTmp.y = std::max(lMinAllowed, lTmp.y);
                    }
                    else
                    {
                        lTmp.y = std::min(lMaxAllowed, lTmp.y);
                    }
                }
                else if (mDirection == EMoveDirection::E_VERTICAL)
                {
                    lMinAllowed = mInitialMousePosition.x - 128;
                    lMaxAllowed = mInitialMousePosition.x + 128;
                    lTmp.y = mInitialMousePosition.y;
                    if (mInitialMousePosition.x > lTmp.x)
                    {
                        lTmp.x = std::max(lMinAllowed, lTmp.x);
                    }
                    else
                    {
                        lTmp.x = std::min(lMaxAllowed, lTmp.x);
                    }
                }
                else
                {
                    if (pow(mInitialMousePosition.x - lTmp.x, 2) > 20)
                    {
                        mDirection = EMoveDirection::E_VERTICAL;
                    }
                    else if (pow(mInitialMousePosition.y - lTmp.y, 2) > 20)
                    {
                        mDirection = EMoveDirection::E_HORIZONTAL;
                    }
                    else
                    {
                        lTmp.x = mInitialMousePosition.x;
                        lTmp.y = mInitialMousePosition.y;
                    }
                }

                Vec2i lCurrentPos = mOwner->GetPosition();
                mOwner->SetPosition(mInitialPosition - (mInitialMousePosition - lTmp));
            }
        }
    }
    void SPieceController::OnEvent(const SDL_Event* aEvent)
    {
        if (aEvent->type == SDL_MOUSEBUTTONUP)
        {
            if(mSelected)
            {
                mOwner->SetPosition(mInitialPosition);
                mLeftPiece = mRightPiece = mTopPiece = mBottomPiece = nullptr;
            }
            mSelected = false;
        }
    }
    void SPieceController::SetSelected(bool aSelected)
    {
        mSelected = aSelected;
        if (mSelected)
        {
            Vec2i lTmp;
            if (SDL_GetMouseState(&lTmp.x, &lTmp.y))
            {
                mInitialPosition = mOwner->GetPosition();
                mInitialMousePosition = lTmp;
                mDirection = EMoveDirection::E_UNKNOWN;

                SMainController* lMainController = dynamic_cast<SMainController*>(CScriptManager::GetInstance()->FindScripByName("SMainController"));
                SDL_assert(lMainController);
                lMainController->GetSurroundingPieces(mPieceLogicPositionX, mPieceLogicPositionY, mLeftPiece, mRightPiece, mTopPiece, mBottomPiece);
            }
        }
    }
}