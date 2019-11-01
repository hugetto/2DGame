//==============================================================================
/*
    
    Hug Beneit
*/
//==============================================================================
#ifndef __SPIECECONTROLLER_H__
#define __SPIECECONTROLLER_H__

#include <json11/json11.hpp>
#include <CScript.h>
#include <utils/Vec2.h>
#include "SMainController.h"

namespace hugGameEngine {
    class CGameObject;
}
using namespace hugGameEngine;

namespace MyGame {
    class SMainController;

    class SPieceController :
        public hugGameEngine::CScript
    {
    private:
        enum class EAction              { E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_TOP, E_MOVE_BOTTOM, E_DELETE, E_NONE };
        
        Vec2i               mPieceLogicPosition     = Vec2i(-1, -1);
        EAction             mAction                 = EAction::E_NONE;
        bool                mComingBack              = false;
        float               mVelocity               = 0.1f;
        bool                mSelected               = false;
        Vec2i               mInitialPosition        = Vec2i();
        Vec2i               mInitialMousePosition   = Vec2i();
        Vec2i               mTextureWidthHeigh      = Vec2i();
        CGameObject*        mLeftPiece              = nullptr;
        CGameObject*        mRightPiece             = nullptr;
        CGameObject*        mTopPiece               = nullptr;
        CGameObject*        mBottomPiece            = nullptr;
        SPieceController*   mLeftPieceScript        = nullptr;
        SPieceController*   mRightPieceScript       = nullptr;
        SPieceController*   mTopPieceScript         = nullptr;
        SPieceController*   mBottomPieceScript      = nullptr;
        SMainController*    mMainController         = nullptr;
    public:
                        SPieceController    (hugGameEngine::CGameObject* aOwner);
                       ~SPieceController    ();
                void    OnCreate            (const hugGameEngine::json11::Json& aJSON);
                void    OnEnable            ();
                void    OnDisable           ();
                void    OnDestroy           ();
        inline  void    SetAction           (EAction aAction) { mAction = aAction; }
                void    Loop                (Uint32 aRenderTime) override;
                void    OnEvent             (const SDL_Event* aEvent);
        inline  void    SetInitialPosition  (const Vec2i& aPos)                 { mInitialPosition = aPos; }
                void    SetSelected         (bool aSelected);
        inline  void    SetPiecePosition    (int aPosX, int aPosY)              { mPieceLogicPosition.x = aPosX; mPieceLogicPosition.y = aPosY; }
        inline  Vec2i   GetPiecePosition    ()                                  { return mPieceLogicPosition; }
    };
}
#endif

