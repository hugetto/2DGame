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
#include <CGameObject.h>

#define PIECES_WIDTH_NUM 5
#define PIECES_HEIGHT_NUM 5

namespace MyGame {
    using namespace hugGameEngine;
    class SMainController :
        public hugGameEngine::CScript
    {
    private:
        CGameObject*    mGrid[PIECES_HEIGHT_NUM][PIECES_WIDTH_NUM];
    public:
                        SMainController         (CGameObject* aOwner, const json11::Json& aJSON);
                       ~SMainController         ();
        void            OnCreate                ();
        void            OnEnable                ();
        void            OnDisable               ();
        void            OnDestroy               ();
        void            Loop                    (Uint32 aRenderTime);
        void            OnEvent                 (const SDL_Event* aEvent);
        void            GetSurroundingPieces    (int aPosX, int aPosY, CGameObject*& aLeftGO, CGameObject*& aRightGO, CGameObject*& aTopGO, CGameObject*& aBottomGO) const;
    };
}
#endif

