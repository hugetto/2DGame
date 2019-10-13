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

#undef main
namespace hugGameEngine
{
    class CApp
    {
    private:
        static CApp Instance;

        bool            mRunning        = true;
        SDL_Window*     mWindow         = NULL;
        SDL_Renderer*   mRenderer       = NULL;
        SDL_Surface*    mPrimarySurface = NULL;

        static const int mWindowWidth   = 1024;
        static const int mWindowHeight  = 768;

    private:
        // Capture SDL Events
        virtual void OnEvent(SDL_Event* Event);

        // Initialize our SDL game / app
        virtual bool Init();

        // Logic loop
        virtual void Loop();

        // Render loop (draw)
        virtual void Render();

        // Free up resources
        virtual void Cleanup();

    public:
                CApp();
        virtual ~CApp();
                CApp    (const CApp& aGo)   = delete;
        CApp& operator= (const CApp&)       = delete;
        virtual int Execute(int argc, char* argv[]);

    public:
        static CApp* GetInstance();

        inline int CApp::GetWindowWidth() const { return mWindowWidth; }
        inline int CApp::GetWindowHeight() const { return mWindowHeight; }
    };
}
#endif //__CAPP_H__
