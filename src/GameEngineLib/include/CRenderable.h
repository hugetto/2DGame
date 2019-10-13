//==============================================================================
/*
    Renderable Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CRENDERABLE_H__
#define __CRENDERABLE_H__

#include <SDL.h>
#include <string>

namespace hugGameEngine
{
    class CRenderable
    {
    private:
        std::string     mFileName   = "";     //C++ 11 allows this initializaiton
        SDL_Renderer*   mRenderer   = nullptr;
        SDL_Texture*    mTexture    = nullptr;
        int             mWidth      = 0;
        int             mHeight     = 0;
    public:
                        CRenderable     () {}
                       ~CRenderable     ();
        int             Load            ( SDL_Renderer* aRenderer, const std::string& aFilename );
        void            Render          () const;
        inline int      GetWidth        () const                  { return mWidth; }
        inline int      GetHeight       () const                  { return mHeight; }
    };
}
#endif //__CRENDERABLE_H__

