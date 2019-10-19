//==============================================================================
/*
    Primary application class
    Hug Beneit
*/
//==============================================================================
#ifndef __CSCRIPT_H__
#define __CSCRIPT_H__

#include <string>
#include <SDL.h>
#include <CComponent.h>
#include <iostream>

namespace hugGameEngine
{
    class CGameObject;
    class CScript : public CComponent
    {
    public:
        CScript(CGameObject* aOwner);
        virtual     ~CScript();
        virtual void OnCreate() = 0;
        virtual void OnEnable() = 0;
        virtual void OnDisable() = 0;
        virtual void OnDestroy() = 0;
        virtual void Loop(unsigned int aRenderTime) = 0;
    };
}

#endif

