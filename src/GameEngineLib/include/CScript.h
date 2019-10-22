//==============================================================================
/*
    Abstract CScript Class
    Hug Beneit
*/
//==============================================================================
#ifndef __CSCRIPT_H__
#define __CSCRIPT_H__

#include <json11/json11.hpp>
#include <string>
#include <SDL.h>
#include <CComponent.h>
#include <iostream>

namespace hugGameEngine
{
    class CGameObject;
    class CScript : public CComponent
    {
    protected:
        const char*     mScriptName;
        json11::Json    mParams;        //Params passed with the data
    public:
        CScript(CGameObject* aOwner, const json11::Json& aParams);
        virtual     ~CScript();
        virtual void OnCreate   () = 0;
        virtual void OnEnable   () = 0;
        virtual void OnDisable  () = 0;
        virtual void OnDestroy  () = 0;
        virtual void Loop       (Uint32 aRenderTime) = 0;
        virtual void OnEvent    (const SDL_Event* aEvent) = 0;
        virtual const char* GetScriptName() { return mScriptName; }
    };
}

#endif

