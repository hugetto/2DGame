#include "pch.h"
#include <CScript.h>

namespace hugGameEngine
{
    CScript::CScript(CGameObject* aOwner) : CComponent(aOwner)
    { 
        mComponentType = CComponent::EComponentType::E_Script;
    }
    CScript::~CScript() {}
}
