#include "SMainController.h"
#include <managers/CGameObjectManager.h>
#include <managers/CTextureManager.h>
#include <CGameObject.h>
#include <utils/Vec2.h>
#include <CRenderable.h>
#include <CSound.h>
#include "../CMyApp.h"
#include "SPieceController.h"

#define PIECE_CFG "./datasource/prefabs/pieces.prefab"

using namespace hugGameEngine;

namespace MyGame {

    SMainController::SMainController(hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON) : CScript(aOwner)
    {
        mScriptName = "SMainController";
    }

    SMainController::~SMainController()
    {

    }
    void SMainController::OnCreate()
    {
        //Create all the pieces from the board
        for (int i = 0; i < mPiecesWidth; i++)
        {
            for (int j = 0; j < mPiecesHeight; j++)
            {
                CMyApp::GetInstance()->CreateObject(PIECE_CFG);
                CGameObject* lPiece = CGameObjectManager::GetInstance()->FindGameObject("piece");
                SDL_assert(lPiece);
                lPiece->SetName(std::string("piece_") + std::to_string(i) + std::string("_") + std::to_string(j));
                CComponent* lRenderer = lPiece->FindFirstComponent(CComponent::EComponentType::E_Renderable);
                SDL_assert(lRenderer);
                Vec2i lPos (i * static_cast<CRenderable*>(lRenderer)->GetWidth(), j * static_cast<CRenderable*>(lRenderer)->GetHeight());
                lPiece->SetPosition(lPos);

                //if(static_cast<CScript*>(lPieceScript)->GetScriptName());
                //CComponent* lSound = lPiece->FindFirstComponent(CComponent::EComponentType::E_Sound);
                //SDL_assert(lSound);
                //static_cast<CSound*>(lSound)->PlayMusic("test1");
            }
        }
    }
    void SMainController::OnEnable()
    {
    }
    void SMainController::OnDisable()
    {
    }
    void SMainController::OnDestroy()
    {
    }
    void SMainController::Loop(Uint32 aRenderTime)
    {
        //mOwner->SetDirection(mOwner->GetDirection() + 2.f);
        //mOwner->SetPosition(mOwner->GetPosition() + Vec2i(1, 1));
    }
    void SMainController::OnEvent(const SDL_Event* aEvent)
    {
        if (aEvent->type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_Point lPoint;
            if (SDL_GetMouseState(&lPoint.x, &lPoint.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                std::vector< CGameObject* > lGameObjectList = CGameObjectManager::GetInstance()->GetGameObjectInPos(lPoint);
                for (CGameObject* lGO : lGameObjectList)
                {
                    SPieceController* lPieceController = lGO->FindFirstScript< SPieceController >("SPieceController");
                    if(lPieceController)
                    {
                        lPieceController->SetSelected(true);
                        //SDL_Log("object name: %s", lGO->GetName().c_str());
                    }
                }
            }
        }
    }
}