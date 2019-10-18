#include "pch.h"
#include "SMainController.h"
#include <CGameObjectManager.h>
#include <CTextureManager.h>
#include <CGameObject.h>
#include <Vec2.h>

#define PIECE_CFG "./datasource/prefabs/piece.prefab"

using namespace hugGameEngine;

const char* MyGame::SMainController::mScriptName = quote(SMainController);
namespace MyGame {

    SMainController::SMainController(hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON) : CScript(aOwner)
    {
    }

    SMainController::~SMainController()
    {

    }
    void SMainController::OnCreate()
    {
        //Create all the pieces
        for (int i = 0; i < mPiecesWidth; i++)
        {
            //Create all the game pieces
            for (int j = 0; j < mPiecesHeight; j++)
            {
                //CMyApp::GetInstance()->CreateObject(PIECE_CFG);
                //hugGameEngine::CGameObject* lPiece = hugGameEngine::CGameObjectManager::GetInstance()->FindGameObject("piece");
                //lPiece->SetName(std::string("piece_") + std::to_string(i) + std::string("_") + std::to_string(j));
                //lPiece->FindFirstComponent(CComponent::EComponentType::E_Renderable);
                //lPiece->SetPosition()
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
    void SMainController::Loop(unsigned int aRenderTime)
    {
        mOwner->SetPosition(mOwner->GetPosition() + Vec2i(1, 1));
    }
}