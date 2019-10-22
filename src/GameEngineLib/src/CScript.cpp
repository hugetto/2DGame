#include "pch.h"
#include <CScript.h>

namespace hugGameEngine
{
    CScript::CScript(CGameObject* aOwner, const json11::Json& aParams) : CComponent(aOwner), mParams(aParams)
    { 
        mComponentType = CComponent::EComponentType::E_Script;
        mScriptName = "CScript";
    }
    CScript::~CScript() {}
}
