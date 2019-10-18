//==============================================================================
/*
    Renderable Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CRENDERABLE_H__
#define __CRENDERABLE_H__

#include <json11/json11.hpp>
#include <SDL.h>
#include <string>
#include <CComponent.h>

namespace hugGameEngine
{
    class CGameObject;

    class CRenderable : public CComponent
    {
    public:
        enum class EPosition { E_FIXED, E_ABSOLUTE };
    private:
        //C++ 11 allows this initializaiton
        SDL_Texture*        mTexture    = nullptr;
        SDL_Rect            mSourcePos  = SDL_Rect();
        int                 mWidth      = 0;
        int                 mHeight     = 0;
        const CGameObject*  mGameObject = nullptr;
        EPosition           mPosition   = EPosition::E_ABSOLUTE;
        SDL_RendererFlip    mFlip       = SDL_FLIP_NONE;
        bool                mUnique     = false;
    public:
                            CRenderable         (CGameObject* aOwner) : CComponent(aOwner){ mComponentType = CComponent::EComponentType::E_Renderable;  }
                           ~CRenderable         ();
                            CRenderable(const CRenderable& aGo) = delete;
                            CRenderable& operator= (const CRenderable&) = delete;
        int                 Load                (const json11::Json& aJSON, SDL_Renderer* aRenderer);
        void                OnRender            (SDL_Renderer* mRenderer) const;
        inline const int&   GetWidth            () const    { return mWidth; }
        inline const int&   GetHeight           () const    { return mHeight; }
        inline const SDL_RendererFlip& GetFlip  () const    { return mFlip; }
    };
}
#endif //__CRENDERABLE_H__

