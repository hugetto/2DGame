#include "pch.h"
#include <CGameObject.h>

namespace hugGameEngine
{
    bool CGameObject::Load(const json11::Json& aJSON)
    {
        bool lOk = false;
        mEnabled = aJSON["enabled"].bool_value(lOk, true);
        mPreviousFrameEnabled = mEnabled;
        mPosition = Vec2i(aJSON["position"].array_items(lOk)[0].int_value(lOk, 0)
                        , aJSON["position"].array_items(lOk)[1].int_value(lOk, 0));
        mRotationAngle = aJSON["rotation"].number_value(lOk, 0.f);
        mScale = Vec2 (aJSON["scale"].array_items(lOk)[0].number_value(lOk, 1.f)
                     , aJSON["scale"].array_items(lOk)[1].number_value(lOk, 1.f));
        mName = aJSON["name"].string_value(lOk);
        return lOk;
    }

    void CGameObject::Loop(unsigned int aRenderTime)
    {
    }

    CComponent* CGameObject::FindFirstComponent(CComponent::EComponentType aType)
    {
        for (std::vector< CComponent* >::const_iterator lIt = mComponentsList.begin(); lIt != mComponentsList.end(); lIt++)
        {
            if ((*lIt)->GetType() == aType)
            {
                return (*lIt);
            }
        }
        return nullptr;
    }
}