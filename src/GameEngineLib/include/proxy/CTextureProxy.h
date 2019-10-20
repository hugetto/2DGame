//==============================================================================
/*
    Renderable Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CTextureProxy_H__
#define __CTextureProxy_H__

#include <SDL.h>
#include <vector>

namespace hugGameEngine
{
    class CGameObject;

    class CTextureProxy
    {
    protected:
        static CTextureProxy sTextureProxyInstance;
    public:
        enum class EPosition { E_FIXED, E_ABSOLUTE };
    private:

        std::vector< SDL_Texture* > mTextureList;
        std::vector< std::string >  mTextureName;
        std::vector< Uint32 >       mTextureCount;
    public:
                            CTextureProxy       () {}
                           ~CTextureProxy       ();
                            CTextureProxy       (const CTextureProxy& aGo) = delete;
                            CTextureProxy& operator= (const CTextureProxy&) = delete;
        SDL_Texture*        CreateTexture       (const char* aTexureFile, SDL_Renderer* aRenderer);
        void                DestroyTexture      (SDL_Texture* aTexture);
        void                DestroyTexture      (const char* aTexureFile);
        static CTextureProxy* GetInstance       ()          { return &CTextureProxy::sTextureProxyInstance; }
    };
}
#endif //__CTextureProxy_H__

