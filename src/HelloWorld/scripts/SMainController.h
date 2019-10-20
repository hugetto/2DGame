//==============================================================================
/*
    Main Controller of the game
    Controls all the small pieces and the Game Init, game end
    Hug Beneit
*/
//==============================================================================
#ifndef __SMAINCONTROLLER_H__
#define __SMAINCONTROLLER_H__

#include <json11/json11.hpp>
#include <CScript.h>

namespace hugGameEngine {
    class CGameObject;
}

namespace MyGame {
    class SMainController :
        public hugGameEngine::CScript
    {
    private:
        int mPiecesWidth    = 0;
        int mPiecesHeight   = 0;
    public:
        SMainController (hugGameEngine::CGameObject* aOwner, const hugGameEngine::json11::Json& aJSON);
        ~SMainController();
        void OnCreate   ();
        void OnEnable   ();
        void OnDisable  ();
        void OnDestroy  ();
        void Loop       (Uint32 aRenderTime);
        void OnEvent    (const SDL_Event* aEvent);
    };
}
#endif

