#include "pch.h"
#include <CTextureManager.h>
#include <CRenderable.h>
#include <CGameObject.h>

namespace hugGameEngine
{
    CTextureManager CTextureManager::sInstance;

    CTextureManager::CTextureManager()
    {

    }

    CTextureManager::~CTextureManager()
    {

    }

    CRenderable* CTextureManager::CreateTexture(const json11::Json& aJSON, CGameObject* aGameObject, SDL_Renderer* aRenderer)
    {
        mRenderableList.push_back(std::make_unique<CRenderable>(aGameObject));
        CRenderable* lRenderObject = mRenderableList.back().get();
        lRenderObject->Load(aJSON, aRenderer);
        return lRenderObject;
    }

    bool CTextureManager::DestroyTexture(const CRenderable* aTexture)
    {
        int lFound = -1;
        for (int i = 0; i< mRenderableList.size(); i++)
        {
            if (mRenderableList[i].get() == aTexture)
            {
                lFound = i;
                break;
            }
        }
        if (lFound >= 0)
        {
            mRenderableList.erase(mRenderableList.begin() + lFound);
        }
        return lFound >= 0;
    }

    void CTextureManager::OnRender(SDL_Renderer* aRenderer) const
    {
        for (std::vector< std::unique_ptr < CRenderable > >::const_iterator lIt = mRenderableList.begin();
            lIt != mRenderableList.end();
            lIt++)
        {
            (*lIt)->OnRender(aRenderer);
        }
    }

}
