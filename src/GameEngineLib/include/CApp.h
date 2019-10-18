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
        static CApp sInstance;

        bool            mRunning        = true;
        SDL_Window*     mWindow         = nullptr;
        SDL_Renderer*   mRenderer       = nullptr;
        SDL_Surface*    mPrimarySurface = nullptr;
        float           mFPSLimit       = 100/3;

        int             mWindowWidth    = 0;
        int             mWindowHeight   = 0;

    public:
                CApp();
        virtual ~CApp();
                CApp    (const CApp& aGo)   = delete;
        CApp& operator= (const CApp&)       = delete;
        virtual int Execute(int argc, char* argv[]);

        // Capture SDL Events
        virtual void OnEvent(SDL_Event* aEvent);

        // Initialize our SDL game / app
        virtual bool Init();

        // Logic loop
        virtual void Loop(unsigned int aRenderTime);

        // Render loop (draw)
        virtual void Render();

        // Free up resources
        virtual void Cleanup();

        virtual int GetWindowWidth()   const { return mWindowWidth; }
        virtual int GetWindowHeight()  const { return mWindowHeight; }

        static CApp* GetInstance();
    };
}
#endif //__CAPP_H__
