#include "pch.h"
#include <CScriptManager.h>
#include <CRenderable.h>
#include <CGameObject.h>
#include <CScript.h>

namespace hugGameEngine
{
    CScriptManager CScriptManager::sInstance;

    CScriptManager::CScriptManager()
    {

    }

    CScriptManager::~CScriptManager()
    {

    }

    void CScriptManager::RegisterScript(CScript* aScript)
    {
        mScriptList.push_back (aScript);
        aScript->OnCreate();
    }

    bool CScriptManager::DestroyScript(const CScript* aScript)
    {
        int lFound = -1;
        for (int i = 0; i< mScriptList.size(); i++)
        {
            if (mScriptList[i] == aScript)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mScriptList.erase(mScriptList.begin() + lFound);
        }
        return lFound >= 0;
    }

    void CScriptManager::Loop(unsigned int aRenterTime)
    {
        for (std::vector< CScript* >::const_iterator lIt = mScriptList.begin();
            lIt != mScriptList.end();
            lIt++)
        {
            (*lIt)->Loop(aRenterTime);
        }
    }

}
