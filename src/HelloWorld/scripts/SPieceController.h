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

namespace hugGameEngine {
    class CGameObject;
}
using namespace hugGameEngine;

namespace MyGame {
    class SPieceController :
        public hugGameEngine::CScript
    {
    private:
        enum class EMoveDirection { E_HORIZONTAL, E_VERTICAL, E_UNKNOWN };

        int             mPiecePosition  = -1;
        EMoveDirection  mDirection      = EMoveDirection::E_UNKNOWN;
        bool            mSelected       = false;
        Vec2i           mInitialPosition = Vec2i();
    public:
                        SPieceController    (hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON);
                       ~SPieceController    ();
                void    OnCreate            ();
                void    OnEnable            ();
                void    OnDisable           ();
                void    OnDestroy           ();
                void    Loop                (Uint32 aRenderTime);
                void    OnEvent             (const SDL_Event* aEvent);
        inline  void    SetInitialPosition  (const Vec2i& aPos)                 { mInitialPosition = aPos; }
        inline  void    SetSelected         (bool aSelected)                    { mSelected = aSelected; }
        inline  void    SetMovementDirection(const EMoveDirection& aDirection)  { mDirection = aDirection; }
    };
}
#endif

