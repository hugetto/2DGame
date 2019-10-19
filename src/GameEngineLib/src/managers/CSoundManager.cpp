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
            mChunkList.erase(mChunkList.begin() + lFound);
        }
        return lFound >= 0;
    }
}
