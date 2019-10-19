//==============================================================================
/*
    Specific application implementation Class
    Hug Beneit
*/
//==============================================================================

#ifndef __CMYAPP_H__
#define __CMYAPP_H__

#include <CApp.h>

using namespace hugGameEngine;

namespace MyGame {
    class CMyApp
    {
    private:
        static CMyApp   sInstance;
        CApp*           mCApp       = nullptr;
        bool            mRunning    = true;
        float           mFPSLimit   = 100 / 3;
    public:
                        CMyApp          () {}
                       ~CMyApp          () {}

        int             Execute         (int argc, char* argv[]);
        void            OnEvent         (SDL_Event* aEvent);
        bool            Init            ();
        void            Loop            (Uint32 aRenderTime);
        void            Render          ();
        void            Cleanup         ();
        bool            CreateObject    (const char* aFileName);
        static CMyApp*  GetInstance     ();
    };
}
#endif //__CMYAPP_H__
