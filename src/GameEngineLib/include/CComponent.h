//==============================================================================
/*
    Component derived class
    Hug Beneit
*/
//==============================================================================
#ifndef __CCOMPONENT_H__
#define __CCOMPONENT_H__

#include <json11/json11.hpp>
#include <SDL.h>

namespace hugGameEngine
{
    class CGameObject;
    class CComponent
    {
    public:
        enum class EComponentType { E_GameObject, E_Renderable, E_Sound, E_Script, E_INVALID };
                                        CComponent          (CGameObject* aOwner)   { mOwner = aOwner; }
        virtual                        ~CComponent          ()                      {};
        virtual EComponentType          GetType             () const                { return mComponentType; }
        virtual CGameObject*            GetGameObject       () const                { return mOwner; }
        virtual bool                    Load                (const json11::Json& aJSON);
        virtual void                    OnCreate() {}
        virtual void                    OnEnable() {}
        virtual void                    OnDisable() {}
        virtual void                    Loop(Uint32 aRenderTime);
        inline  bool                    Enabled             () const                { return mEnabled; }
        inline  void                    EnableComponent     ()                      { mEnabled = true; mPreviousFrameEnabled = false; }
        inline  void                    DisableComponent    ()                      { mEnabled = false; mPreviousFrameEnabled = true; }
                bool                    ShouldCallOnEnable  ();
                bool                    ShouldCallOnDisable ();
    protected:
        CGameObject*    mOwner                  = nullptr;
        EComponentType  mComponentType          = EComponentType::E_INVALID;
        bool            mEnabled                = true;
        bool            mPreviousFrameEnabled   = false;
    };
}

#endif

