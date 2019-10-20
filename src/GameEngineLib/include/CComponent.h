//==============================================================================
/*
    Component derived class
    Hug Beneit
*/
//==============================================================================
#ifndef __CCOMPONENT_H__
#define __CCOMPONENT_H__

namespace hugGameEngine
{
    class CGameObject;
    class CComponent
    {
    public:
        enum class EComponentType { E_GameObject, E_Renderable, E_Sound, E_Script, E_INVALID };
                                        CComponent      (CGameObject* aOwner) { mOwner = aOwner; }
        virtual                        ~CComponent      ()          {};
        virtual inline EComponentType   GetType         () const    { return mComponentType; }
        virtual inline CGameObject*     GetGameObject   () const    { return mOwner; }
    protected:
        CGameObject*mOwner;
        EComponentType mComponentType = EComponentType::E_INVALID;
    };
}

#endif

