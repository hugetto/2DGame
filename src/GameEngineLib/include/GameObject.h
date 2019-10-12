//==============================================================================
/*
    GameObject Class
    Hug Beneit
*/
//==============================================================================
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <Vec2.h>

namespace hugGameEngine
{
    class GameObject
    {
    private:
        Vec2    mPosition;
        Vec2    mDirection;
        Vec2    mScale;

    public:
                        GameObject      () : mPosition(0.f,0.f), mDirection(0.f,0.f), mScale(0.f,0.f) {}
                       ~GameObject      ()  {}
        const Vec2&     GetPosition     ()  { return mPosition; }
        const Vec2&     GetDirection    ()  { return mDirection; }
        const Vec2&     GetDirection    ()  { return mScale; }
        void            OnCreate        ()  {}
        void            Update          ()  {}
    };
}

#endif //__GAMEOBJECT_H_