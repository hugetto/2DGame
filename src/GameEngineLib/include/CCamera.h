//==============================================================================
/*
    Primary application class
    Hug Beneit
*/
//==============================================================================
#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include <utils/Vec2.h>
#include <SDL.h>

namespace hugGameEngine
{
    class CCamera
    {
    private:
        static CCamera sCameraInstance;
        Vec2i       mCameraPosition     = Vec2i(0, 0);
        Vec2i       mDesiredPosition    = Vec2i(0, 0);
        Vec2i       mSpeed              = Vec2i(0, 0);
    public:
        CCamera() {}
        ~CCamera() {}
        inline const Vec2i& GetCameraPosition() const               { return mCameraPosition; }
        inline void         SetCameraPosition(const Vec2i& aNewPos) { mDesiredPosition = aNewPos; }
        inline void         Loop(Uint32 aTime)                      { mCameraPosition += ((mDesiredPosition * mSpeed) * aTime); }
        static CCamera*     GetInstance()                           { return &CCamera::sCameraInstance; }
    };
}
#endif

