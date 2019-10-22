#include "pch.h"
#include <managers/CScriptManager.h>
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
        for (CScript* lPointer : mScriptList)
        {
            delete(lPointer);
        }
        mScriptList.clear();
    }

    void CScriptManager::RegisterScript(CScript* aScript)
    {
        mScriptList.push_back (aScript);
        aScript->OnCreate();
    }

    bool CScriptManager::DestroyScript(const CScript* aScript)
    {
        int lFound = -1;
        for (size_t i = 0; i< mScriptList.size(); i++)
        {
            if (mScriptList[i] == aScript)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            delete(aScript);
            mScriptList.erase(mScriptList.begin() + lFound);
        }
        return lFound >= 0;
    }

    void CScriptManager::Loop(Uint32 aRenterTime)
    {
        for (std::vector< CScript* >::const_iterator lIt = mScriptList.begin();
            lIt != mScriptList.end();
            lIt++)
        {
            (*lIt)->Loop(aRenterTime);
        }
    }

    void CScriptManager::OnEvent(const SDL_Event* aEvent)
    {
        for (std::vector< CScript* >::const_iterator lIt = mScriptList.begin();
            lIt != mScriptList.end();
            lIt++)
        {
            (*lIt)->OnEvent(aEvent);
        }
    }
    CScript* CScriptManager::FindScripByName(const char* aScriptType)
    {
        for (std::vector< CScript* >::iterator lIt = mScriptList.begin();
            lIt != mScriptList.end();
            lIt++)
        {
            if (SDL_strcasecmp((*lIt)->GetScriptName(), aScriptType) == 0)
                return (*lIt);
        }
        return nullptr;
    }

    std::vector< CScript* > CScriptManager::FindAllScripByName(const char* aScriptType)
    {
        std::vector< CScript* > lRet;
        for (std::vector< CScript* >::iterator lIt = mScriptList.begin();
            lIt != mScriptList.end();
            lIt++)
        {
            if (SDL_strcasecmp((*lIt)->GetScriptName(), aScriptType) == 0)
                lRet.push_back(*lIt);
        }
        return lRet;
    }
}
