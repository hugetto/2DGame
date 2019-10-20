#include "pch.h"
#include <managers/CGameObjectManager.h>
#include <CGameObject.h>
#include <algorithm>
#include <CCamera.h>

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
        mGameObjectList.push_back(new CGameObject());
        CGameObject* lGameObject = mGameObjectList.back();
        lGameObject->Load(aJSON);
        return lGameObject;
    }

    CGameObject* CGameObjectManager::FindGameObject(const char* aGameObjectName) const
    {
        CGameObject* lRetObject = nullptr;
        for (CGameObject* lGameObject : mGameObjectList)
        {
            if (strcmp(lGameObject->GetName().c_str(), aGameObjectName) == 0)
            {
                lRetObject = lGameObject;
                break;
            }
        }
        return lRetObject;
    }

    bool CGameObjectManager::DestroyGameObject(const CGameObject* aGameObject)
    {
        std::vector< CGameObject* >::const_iterator lIt = std::begin(mGameObjectList);
        bool lFound = false;
        while (lIt != std::end(mGameObjectList))
        {
            if (aGameObject == (*lIt))
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
            SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "GameObject %s not found", aGameObject->GetName().c_str());
        }

        return lFound;
    }

    void CGameObjectManager::Loop(unsigned int aRenderTime) const
    {
        for (std::vector< CGameObject* >::const_iterator lIt = mGameObjectList.begin();
            lIt != mGameObjectList.end();
            lIt++)
        {
            (*lIt)->Loop(aRenderTime);
        }
    }


    std::vector< CGameObject* > CGameObjectManager::GetGameObjectInPos(const SDL_Point* aPosition) const
    {
        std::vector< CGameObject* > lRet;
        for (CGameObject* lGO : mGameObjectList)
        {
            if (lGO->PointInGameObject(aPosition))
            {
                lRet.push_back(lGO);
            }
        }
        return lRet;
    }
}
