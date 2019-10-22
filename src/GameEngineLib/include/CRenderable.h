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
        enum class EPosition    { E_FIXED, E_ABSOLUTE };
        enum class EReference   { 
                                    E_TOP_LEFT   , E_TOP_CENTER   , E_TOP_RIGHT,
                                    E_MIDDLE_LEFT, E_MIDDLE_CENTER, E_MIDDLE_RIGHT,
                                    E_BOTTOM_LEFT, E_BOTTOM_CENTER, E_BOTTOM_RIGHT
                                };
    private:
        //C++ 11 allows this initializaiton
        SDL_Texture*        mTexture    = nullptr;
        SDL_Rect            mSourcePos  = SDL_Rect();
        int                 mWidth      = 0;
        int                 mHeight     = 0;
        EPosition           mPosition   = EPosition::E_ABSOLUTE;
        SDL_RendererFlip    mFlip       = SDL_FLIP_NONE;
        bool                mUnique     = false;
        Uint32              mLayer      = 0;
        EReference          mReference  = EReference::E_TOP_LEFT;
        bool                mActive     = true;
        std::string         mName       = "";
    public:
                            CRenderable         (CGameObject* aOwner) : CComponent(aOwner){ mComponentType = CComponent::EComponentType::E_Renderable;  }
                           ~CRenderable         ();
                            CRenderable         (const CRenderable& aGo) = delete;
                            CRenderable& operator= (const CRenderable&) = delete;
        int                 Load                (const json11::Json& aJSON);
        void                OnRender            (SDL_Renderer* mRenderer) const;
        inline const int&   GetWidth            () const    { return mWidth; }
        inline const int&   GetHeight           () const    { return mHeight; }
        inline const SDL_RendererFlip& GetFlip  () const    { return mFlip; }
        inline Uint32       GetLayer            () const    { return mLayer; }
        inline std::string  GetName             () const    { return mName; }
               bool         PointInPos          (const SDL_Point& aPoint) const;

    private:
        const SDL_Rect      GetRectPosition     () const ;
    };
}
#endif //__CRENDERABLE_H__

