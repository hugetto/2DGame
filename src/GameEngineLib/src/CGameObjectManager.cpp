#include "pch.h"
#include <CGameObjectManager.h>
#include <CGameObject.h>
#include <algorithm>
#include <CLog.h>

namespace hugGameEngine
{
    CGameObjectManager CGameObjectManager::sInstance;

    CGameObjectManager::CGameObjectManager()
    {

    }

    CGameObjectManager::~CGameObjectManager()
    {

    }

    CGameObject* CGameObjectManager::CreateGameObject(const json11::Json& aJSON)
    {
        mGameObjectList.push_back(std::make_unique<CGameObject>());
        CGameObject* lGameObject = mGameObjectList.back().get();
        lGameObject->Load(aJSON);
        return lGameObject;
    }

    CGameObject* CGameObjectManager::FindGameObject(const char* aGameObjectName)
    {
        CGameObject* lRetObject = nullptr;
        for (std::unique_ptr < CGameObject >& lGameObject : mGameObjectList)
        {
            if (strcmp(lGameObject->GetName().c_str(), aGameObjectName) == 0)
            {
                lRetObject = lGameObject.get();
                break;
            }
        }
        return lRetObject;
    }

    bool CGameObjectManager::DestroyGameObject(const CGameObject* aGameObject)
    {
        std::vector< std::unique_ptr < CGameObject > >::const_iterator lIt = std::begin(mGameObjectList);
        bool lFound = false;
        while (lIt != std::end(mGameObjectList))
        {
            if (aGameObject == (*lIt).get())
            {
                lFound = true;
                mGameObjectList.erase(lIt);
                break;
            }
            else
            {
                ++lIt;
            }
        }

        if(!lFound)
        {
            CLog("GameObject %s not found", aGameObject->GetName());
        }

        return lFound;
    }

    void CGameObjectManager::Loop(unsigned int aRenderTime)
    {
        for (std::vector< std::unique_ptr < CGameObject > >::const_iterator lIt = mGameObjectList.begin();
            lIt != mGameObjectList.end();
            lIt++)
        {
            (*lIt)->Loop(aRenderTime);
        }
    }
}
