#include "pch.h"
#include <CSoundManager.h>
#include <CSound.h>

namespace hugGameEngine
{
    CSoundManager CSoundManager::sInstance;

    CSoundManager::CSoundManager()
    {

    }

    CSoundManager::~CSoundManager()
    {

    }

    CSound* CSoundManager::CreateSound(const json11::Json& aJSON, CGameObject* aGameObject, SDL_Renderer* aRenderer)
    {
        mSoundList.push_back(std::make_unique<CSound>());
        CSound* lSound = mSoundList.back().get();
        lSound->Load(aJSON, aGameObject, aRenderer);
        return lSound;
    }

    bool CSoundManager::DestroySound(const CSound* aTexture)
    {
        int lFound = -1;
        for (int i = 0; i < mSoundList.size(); i++)
        {
            if (mSoundList[i].get() == aTexture)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mSoundList.erase(mSoundList.begin() + lFound);
        }
        return lFound >= 0;
    }

    void CSoundManager::OnRender(SDL_Renderer* aRenderer) const
    {
        for (std::vector< std::unique_ptr < CSound > >::const_iterator lIt = mSoundList.begin();
            lIt != mSoundList.end();
            lIt++)
        {
            //(*lIt)->OnRender(aRenderer);
        }
    }

}
