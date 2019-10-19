//==============================================================================
/*
    Primary application class
    Hug Beneit
*/
//==============================================================================
#ifndef __CAPP_H__
#define __CAPP_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_audio.h>

#undef main
namespace hugGameEngine
{
    class CApp
    {
    protected:
        SDL_Window*     mWindow         = nullptr;
        SDL_Renderer*   mRenderer       = nullptr;
        SDL_Surface*    mPrimarySurface = nullptr;
        float           mFPSLimit       = 100/3;

        int             mWindowWidth    = 0;
        int             mWindowHeight   = 0;

    public:
                CApp();
        ~CApp();
                CApp    (const CApp& aGo)   = delete;
        CApp& operator= (const CApp&)       = delete;
        int Execute(int argc, char* argv[]);

        // Capture SDL Events
        void OnEvent(SDL_Event* aEvent);

        // Initialize our SDL game / app
        bool Init();

        // Logic loop
        void Loop(unsigned int aRenderTime);

        // Render loop (draw)
        void Render();

        // Free up resources
        void Cleanup();

        inline Uint32              GetWindowWidth      () const { return mWindowWidth; }
        inline Uint32              GetWindowHeight     () const { return mWindowHeight; }
        inline float            GetFPSLimit         () const { return mFPSLimit; }
        inline SDL_Renderer*    GetRenderer         () const { return mRenderer; }
    };
}
#endif //__CAPP_H__
