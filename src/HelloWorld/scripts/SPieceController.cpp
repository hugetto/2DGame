#include "SPieceController.h"
#include "SMainController.h"
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

    SPieceController::SPieceController(hugGameEngine::CGameObject* aOwner) : 
        CScript(aOwner)
    {
        mScriptName = "SPieceController";
    }

    SPieceController::~SPieceController()
    {

    }
    void SPieceController::OnCreate(const hugGameEngine::json11::Json& aJSON)
    {
    }
    void SPieceController::OnEnable()
    {
        CComponent* lRenderer = mOwner->FindFirstComponent(CComponent::EComponentType::E_Renderable);
        SDL_assert(lRenderer);
        mTextureWidthHeigh.x = static_cast<CRenderable*>(lRenderer)->GetWidth();
        mTextureWidthHeigh.y = static_cast<CRenderable*>(lRenderer)->GetHeight();
        mOwner->SetPosition(mPieceLogicPosition * mTextureWidthHeigh);

        mMainController = dynamic_cast<SMainController*>(CScriptManager::GetInstance()->FindScripByName("SMainController"));
        SDL_assert(mMainController);
    }
    void SPieceController::OnDisable()
    {
    }
    void SPieceController::OnDestroy()
    {
    }
    void SPieceController::Loop(Uint32 aRenderTime)
    {
        if (mAction != EAction::E_NONE)
        {
            Vec2i lCurrentPos = mOwner->GetPosition();
            switch (mAction)
            {
            case MyGame::SPieceController::EAction::E_MOVE_LEFT:
                if (mComingBack)
                {
                    lCurrentPos.x += static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.x >= mInitialPosition.x)
                    {
                        lCurrentPos.x = mInitialPosition.x;
                        mAction = MyGame::SPieceController::EAction::E_NONE;
                        mComingBack = false;
                        mSelected = false;
                        mLeftPiece = mRightPiece = mTopPiece = mBottomPiece = nullptr;
                        mLeftPieceScript = mRightPieceScript = mTopPieceScript = mBottomPieceScript = nullptr;
                    }
                }
                else
                {
                    lCurrentPos.x -= static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.x <= mInitialPosition.x - mTextureWidthHeigh.x)
                    {
                        lCurrentPos.x = mInitialPosition.x - mTextureWidthHeigh.x;
                        bool lHaveToReturn = true;
                        if (mSelected)
                        {
                            mMainController->Swap(GetPiecePosition(), mLeftPieceScript->GetPiecePosition());
                            if (mMainController->CheckScene()) //Checks the elements in the scene (3 or plus in a row)
                            {
                                lHaveToReturn = false;
                            }
                            else
                            {
                                mMainController->Swap(mLeftPieceScript->GetPiecePosition(), GetPiecePosition());
                            }
                        }
                        mComingBack = lHaveToReturn;
                    }
                }
                break;
            case MyGame::SPieceController::EAction::E_MOVE_RIGHT:
                if (mComingBack)
                {
                    lCurrentPos.x -= static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.x <= mInitialPosition.x)
                    {
                        lCurrentPos.x = mInitialPosition.x;
                        mAction = MyGame::SPieceController::EAction::E_NONE;
                        mComingBack = false;
                        mSelected = false;
                        mLeftPiece = mRightPiece = mTopPiece = mBottomPiece = nullptr;
                        mLeftPieceScript = mRightPieceScript = mTopPieceScript = mBottomPieceScript = nullptr;
                    }
                }
                else
                {
                    lCurrentPos.x += static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.x >= mInitialPosition.x + mTextureWidthHeigh.x)
                    {
                        lCurrentPos.x = mInitialPosition.x + mTextureWidthHeigh.x;
                        bool lHaveToReturn = true;
                        if (mSelected)
                        {
                            mMainController->Swap(GetPiecePosition(), mRightPieceScript->GetPiecePosition());
                            if (mMainController->CheckScene()) //Checks the elements in the scene (3 or plus in a row)
                            {
                                lHaveToReturn = false;
                            }
                            else
                            {
                                mMainController->Swap(mRightPieceScript->GetPiecePosition(), GetPiecePosition());
                            }
                        }
                        mComingBack = lHaveToReturn;
                    }
                }
                break;
            case MyGame::SPieceController::EAction::E_MOVE_TOP:
                if (mComingBack)
                {
                    lCurrentPos.y += static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.y >= mInitialPosition.y)
                    {
                        lCurrentPos.y = mInitialPosition.y;
                        mAction = MyGame::SPieceController::EAction::E_NONE;
                        mComingBack = false;
                        mSelected = false;
                        mLeftPiece = mRightPiece = mTopPiece = mBottomPiece = nullptr;
                        mLeftPieceScript = mRightPieceScript = mTopPieceScript = mBottomPieceScript = nullptr;
                    }
                }
                else
                {
                    lCurrentPos.y -= static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.y <= mInitialPosition.y - mTextureWidthHeigh.y)
                    {
                        lCurrentPos.y = mInitialPosition.y - mTextureWidthHeigh.y;
                        bool lHaveToReturn = true;
                        if (mSelected)
                        {
                            mMainController->Swap(GetPiecePosition(), mTopPieceScript->GetPiecePosition());
                            if (mMainController->CheckScene()) //Checks the elements in the scene (3 or plus in a row)
                            {
                                lHaveToReturn = false;
                            }
                            else
                            {
                                mMainController->Swap(mTopPieceScript->GetPiecePosition(), GetPiecePosition());
                            }
                        }
                        mComingBack = lHaveToReturn;
                    }
                }
                break;
            case MyGame::SPieceController::EAction::E_MOVE_BOTTOM:
                if (mComingBack)
                {
                    lCurrentPos.y -= static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.y <= mInitialPosition.y)
                    {
                        lCurrentPos.y = mInitialPosition.y;
                        mAction = MyGame::SPieceController::EAction::E_NONE;
                        mComingBack = false;
                        mSelected = false;
                        mLeftPiece = mRightPiece = mTopPiece = mBottomPiece = nullptr;
                        mLeftPieceScript = mRightPieceScript = mTopPieceScript = mBottomPieceScript = nullptr;
                    }
                }
                else
                {
                    lCurrentPos.y += static_cast<int>(aRenderTime * mVelocity);
                    if (lCurrentPos.y >= mInitialPosition.y + mTextureWidthHeigh.y)
                    {
                        lCurrentPos.y = mInitialPosition.y + mTextureWidthHeigh.y;
                        bool lHaveToReturn = true;
                        if (mSelected)
                        {
                            mMainController->Swap(GetPiecePosition(), mBottomPieceScript->GetPiecePosition());
                            if (mMainController->CheckScene()) //Checks the elements in the scene (3 or plus in a row)
                            {
                                lHaveToReturn = false;
                            }
                            else
                            {
                                mMainController->Swap(mBottomPieceScript->GetPiecePosition(), GetPiecePosition());
                            }
                        }
                        mComingBack = lHaveToReturn;
                    }
                }
                break;
            case MyGame::SPieceController::EAction::E_NONE:
                break;
            default:
                break;
            }
            mOwner->SetPosition(lCurrentPos);
        }
        else if (mSelected && mAction == EAction::E_NONE)
        {
            Vec2i lTmp;
            if (SDL_GetMouseState(&lTmp.x, &lTmp.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                if (mTopPieceScript && mInitialMousePosition.y - lTmp.y > 10)
                {
                    mAction = EAction::E_MOVE_TOP;
                    lTmp.x = mInitialMousePosition.x;
                    mTopPieceScript->SetAction(EAction::E_MOVE_BOTTOM);
                }
                else if (mLeftPieceScript && mInitialMousePosition.x - lTmp.x > 10)
                {
                    mAction = EAction::E_MOVE_LEFT;
                    lTmp.y = mInitialMousePosition.y;
                    mLeftPieceScript->SetAction(EAction::E_MOVE_RIGHT);
                }
                else if (mBottomPieceScript && mInitialMousePosition.y - lTmp.y < -10)
                {
                    mAction = EAction::E_MOVE_BOTTOM;
                    lTmp.x = mInitialMousePosition.x;
                    mBottomPieceScript->SetAction(EAction::E_MOVE_TOP);
                }
                else if (mRightPieceScript && mInitialMousePosition.x - lTmp.x < -10)
                {
                    mAction = EAction::E_MOVE_RIGHT;
                    lTmp.y = mInitialMousePosition.y;
                    mRightPieceScript->SetAction(EAction::E_MOVE_LEFT);
                }
                else
                {
                    lTmp.x = mInitialMousePosition.x;
                    lTmp.y = mInitialMousePosition.y;
                }
                mOwner->SetPosition(mInitialPosition - (mInitialMousePosition - lTmp));
            }
        }
    }
    void SPieceController::OnEvent(const SDL_Event* aEvent)
    {
    }
    void SPieceController::SetSelected(bool aSelected)
    {
        if (!mSelected && mAction == EAction::E_NONE)
        {
            mSelected = aSelected;
            Vec2i lTmp;
            if (SDL_GetMouseState(&lTmp.x, &lTmp.y))
            {
                mInitialPosition = mOwner->GetPosition();
                mInitialMousePosition = lTmp;

                mMainController->GetSurroundingPieces(mPieceLogicPosition, mLeftPiece, mRightPiece, mTopPiece, mBottomPiece);
                if (mLeftPiece)
                {
                    mLeftPieceScript = dynamic_cast<SPieceController*>(mLeftPiece->FindFirstComponent(CComponent::EComponentType::E_Script));
                    SDL_assert(mLeftPieceScript);
                    mLeftPieceScript->SetInitialPosition(mLeftPiece->GetPosition());
                }
                if (mRightPiece)
                {
                    mRightPieceScript = dynamic_cast<SPieceController*>(mRightPiece->FindFirstComponent(CComponent::EComponentType::E_Script));
                    SDL_assert(mRightPieceScript);
                    mRightPieceScript->SetInitialPosition(mRightPiece->GetPosition());
                }
                if (mTopPiece)
                {
                    mTopPieceScript = dynamic_cast<SPieceController*>(mTopPiece->FindFirstComponent(CComponent::EComponentType::E_Script));
                    SDL_assert(mTopPieceScript);
                    mTopPieceScript->SetInitialPosition(mTopPiece->GetPosition());
                }
                if (mBottomPiece)
                {
                    mBottomPieceScript = dynamic_cast<SPieceController*>(mBottomPiece->FindFirstComponent(CComponent::EComponentType::E_Script));
                    SDL_assert(mBottomPieceScript);
                    mBottomPieceScript->SetInitialPosition(mBottomPiece->GetPosition());
                }
            }
        }
    }
}