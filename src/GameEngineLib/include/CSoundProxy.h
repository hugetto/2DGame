//==============================================================================
/*
    Renderable Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CSOUNDPROXY_H__
#define __CSOUNDPROXY_H__

#include <SDL.h>
#include <vector>

namespace hugGameEngine
{
    class CGameObject;

    class CSoundProxy
    {
    protected:
        static CSoundProxy sTextureProxyInstance;
    public:
        enum class EPosition { E_FIXED, E_ABSOLUTE };
    private:

        std::vector< SDL_Texture* >     mTextureList;
        std::vector< std::string >      mTextureName;
        std::vector< unsigned int >     mTextureCount;
    public:
                            CSoundProxy       () {}
                           ~CSoundProxy       ();
                            CSoundProxy       (const CSoundProxy& aGo) = delete;
                            CSoundProxy& operator= (const CSoundProxy&) = delete;
        SDL_Texture*        CreateTexture       (const char* aTexureFile, SDL_Renderer* aRenderer);
        void                DestroyTexture      (SDL_Texture* aTexture);
        void                DestroyTexture      (const char* aTexureFile);
        static CSoundProxy* GetInstance       ()          { return &CSoundProxy::sTextureProxyInstance; }
    };
}
#endif

