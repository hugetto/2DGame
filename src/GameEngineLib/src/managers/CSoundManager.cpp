#include "pch.h"
#include <managers/CSoundManager.h>
#include <CSound.h>

namespace hugGameEngine
{
    CSoundManager CSoundManager::sSoundManagerInstance;

    CSoundManager::CSoundManager()
    {
    }

    CSoundManager::~CSoundManager()
    {
        for (CSound* lSound : mChunkList)
        {
            delete (lSound);
        }
        mChunkList.clear();
    }

    CSound* CSoundManager::CreateSound(const json11::Json& aJSON, CGameObject* aGameObject)
    {
        mChunkList.push_back(new CSound(aGameObject));
        CSound* lSound = mChunkList.back();
        lSound->Load(aJSON, aGameObject);
        return lSound;
    }

    bool CSoundManager::DestroySound(const CSound* aSound)
    {
        int lFound = -1;
        for (size_t i = 0; i < mChunkList.size(); i++)
        {
            if (mChunkList[i] == aSound)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            delete (aSound);
            mChunkList.erase(mChunkList.begin() + lFound);
        }
        return lFound >= 0;
    }

    CSound* CSoundManager::FindSoundByName(const char* aSoundName)
    {
        for (std::vector< CSound* >::iterator lIt = mChunkList.begin();
            lIt != mChunkList.end();
            lIt++)
        {
            if ((*lIt)->HasSound(aSoundName))
                return (*lIt);
        }
        return nullptr;
    }

    std::vector< CSound* > CSoundManager::FindAllSoundsByName(const char* aSoundName)
    {
        std::vector< CSound* > lRet;
        for (std::vector< CSound* >::iterator lIt = mChunkList.begin();
            lIt != mChunkList.end();
            lIt++)
        {
            if ((*lIt)->HasSound(aSoundName))
                lRet.push_back(*lIt);
        }
        return lRet;
    }
}
