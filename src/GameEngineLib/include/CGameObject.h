//==============================================================================
/*
    GameObject Class
    Hug Beneit
*/
//==============================================================================
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <Vec2.h>
#include <string>

namespace hugGameEngine
{
    class CGameObject
    {
    private:
        bool            mEnabled                = false;  //C++ 11 allows this initializaiton
        bool            mPreviousFrameEnabled   = false;
        Vec2            mPosition               = Vec2( 0.f, 0.f );
        Vec2            mDirection              = Vec2( 0.f, 0.f );
        Vec2            mScale                  = Vec2( 0.f, 0.f );
        std::string     mName                   = "";

    public:
                        CGameObject     ()  {}
                       ~CGameObject     ()  {}
                        CGameObject     ( const CGameObject& aGo )    = delete;
        CGameObject&    operator=       ( const CGameObject& )        = delete;
        inline const Vec2&     GetPosition     () const    { return mPosition; }
        inline const Vec2&     GetDirection    () const    { return mDirection; }
        inline const Vec2&     GetScale        () const    { return mScale; }
        void            OnCreate        ()          {}
        void            OnEnable        ()          {}
        void            OnDisable       ()          {}
        void            Update          ()          {}
        void            SetName         ( const std::string& aName ) { mName = aName; }
    };
}

#endif //__GAMEOBJECT_H_