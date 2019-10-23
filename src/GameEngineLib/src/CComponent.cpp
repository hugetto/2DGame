#include "pch.h"
#include <CComponent.h>

namespace hugGameEngine
{
    bool CComponent::Load(const json11::Json& aParams)
    {
        bool lOk = true;
        mEnabled = aParams["enabled"].bool_value(lOk, true);
        mPreviousFrameEnabled = !mEnabled;
        return true;
    }

    bool CComponent::ShouldCallOnEnable()
    { 
        if (mEnabled && !mPreviousFrameEnabled)
        {
            mPreviousFrameEnabled = mEnabled;
            return true;
        }
        else
            return false;
    }
    bool CComponent::ShouldCallOnDisable()
    {
        if (!mEnabled && mPreviousFrameEnabled)
        {
            mPreviousFrameEnabled = mEnabled;
            return true;
        }
        else
            return false;
    }
    void CComponent::Loop(Uint32 aRenderTime)
    {
    }
}
