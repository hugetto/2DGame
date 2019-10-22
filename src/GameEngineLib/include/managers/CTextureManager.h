//==============================================================================
/*
    Stores all the textures and render them in a ordered way
    Hug Beneit
*/
//==============================================================================
#ifndef __CTEXTUREMANAGER_H__
#define __CTEXTUREMANAGER_H__

#include <json11/json11.hpp>
#include <SDL.h>
#include <vector>
#include <memory>

namespace hugGameEngine
{
    class CGameObject;
    class CRenderable;

    class CTextureManager {
    private:
        static CTextureManager sInstance;
        std::vector< CRenderable*> mRenderableList;
    public:
        CTextureManager             ();
        ~CTextureManager            ();
        CTextureManager             (const CTextureManager& aGo) = delete;
        CTextureManager& operator=  (const CTextureManager&) = delete;

        inline static CTextureManager* GetInstance() { return &CTextureManager::sInstance; }

        CRenderable*                CreateTexture           (const json11::Json& aJSON, CGameObject* aGameObject);
        bool                        DestroyTexture          (const CRenderable* aTexture);
        void                        OnRender                (SDL_Renderer* aRenderer) const;
        CRenderable*                FindTextureByName       (const char* aTextureName);
        std::vector< CRenderable* > FindAllTextureByName    (const char* aTextureName);
    };
}

#endif