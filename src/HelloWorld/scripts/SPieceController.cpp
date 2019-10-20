#include "SPieceController.h"
#include <managers/CGameObjectManager.h>
#include <managers/CTextureManager.h>
#include <CGameObject.h>
#include <utils/Vec2.h>
#include <CRenderable.h>
#include <CSound.h>

#define PIECE_CFG "./datasource/prefabs/pieces.prefab"

using namespace hugGameEngine;

namespace MyGame {

    SPieceController::SPieceController(hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON) : CScript(aOwner)
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
    }
    void SPieceController::OnDisable()
    {
    }
    void SPieceController::OnDestroy()
    {
    }
    void SPieceController::Loop(Uint32 aRenderTime)
    {
    }
    void SPieceController::OnEvent(const SDL_Event* aEvent)
    {
    }
}