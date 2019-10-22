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

    SMainController::SMainController(hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON) : CScript(aOwner, aJSON)
    {
        mScriptName = "SMainController";
    }

    SMainController::~SMainController()
    {

    }
    void SMainController::OnCreate()
    {
        //Create all the pieces from the board
        for (int i = 0; i < PIECES_WIDTH_NUM; i++)
        {
            for (int j = 0; j < PIECES_HEIGHT_NUM; j++)
            {
                CMyApp::GetInstance()->CreateObject(PIECE_CFG);
                CGameObject* lPiece = CGameObjectManager::GetInstance()->FindGameObject("piece");
                SDL_assert(lPiece);
                lPiece->SetName(std::string("piece_") + std::to_string(i) + std::string("_") + std::to_string(j));
                CComponent* lRenderer = lPiece->FindFirstComponent(CComponent::EComponentType::E_Renderable);
                SDL_assert(lRenderer);
                Vec2i lPos (i * static_cast<CRenderable*>(lRenderer)->GetWidth(), j * static_cast<CRenderable*>(lRenderer)->GetHeight());
                lPiece->SetPosition(lPos);

                SPieceController* lScript = dynamic_cast<SPieceController*>(lPiece->FindFirstComponent(CComponent::EComponentType::E_Script));
                SDL_assert(lScript);
                lScript->SetPiecePosition(i, j);

                //store game objects in a grid
                mGrid[i][j] = lPiece;
                
                //CScript* lScript = CScriptManager::GetInstance()->FindScripByName("SMainController");
                //SDL_assert(lScript);
                //mMainController = dynamic_cast<SMainController*>(lScript);
                
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

    void SMainController::GetSurroundingPieces(int aPosX, int aPosY, CGameObject*& aLeftGO, CGameObject*& aRightGO, CGameObject*& aTopGO, CGameObject*& aBottomGO) const
    {
        if (aPosX == 0)
            aLeftGO = nullptr;
        else
            aLeftGO     = mGrid[aPosX - 1]  [aPosY];
        if (aPosX == PIECES_HEIGHT_NUM)
            aRightGO = nullptr;
        else
            aRightGO    = mGrid[aPosX + 1]  [aPosY];
        if (aPosY == 0)
            aTopGO = nullptr;
        else
            aTopGO      = mGrid[aPosX]      [aPosY - 1];
        if (aPosY == PIECES_WIDTH_NUM)
            aBottomGO = nullptr;
        else
            aBottomGO   = mGrid[aPosX]      [aPosY + 1];
    }
}