//==============================================================================
/*
    Specific application implementation Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CMYAPP_H__
#define __CMYAPP_H__

#include <CApp.h>

namespace MyGame {
    class CMyApp : public hugGameEngine::CApp
    {
    private:
        static CMyApp Instance;
    public:
        CMyApp() {}
        ~CMyApp() {}

        int Execute(int argc, char* argv[]);
        void OnEvent(SDL_Event* aEvent);
        bool Init();
        void Loop(unsigned int aRenderTime);
        void Render();
        void Cleanup();
        bool CreateObject(const char* aFileName);

        int GetWindowWidth()   const { return mWindowWidth; }
        int GetWindowHeight()  const { return mWindowHeight; }
        static CMyApp* GetInstance();
    };
}
#endif //__CMYAPP_H__
