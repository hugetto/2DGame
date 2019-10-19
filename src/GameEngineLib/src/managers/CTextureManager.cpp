#include "pch.h"
#include <managers/CTextureManager.h>
#include <CRenderable.h>
#include <CGameObject.h>
#include <algorithm>

namespace hugGameEngine
{
    CTextureManager CTextureManager::sInstance;

    bool SortTextureByLayers(CRenderable* aTex1, CRenderable* aTex2)
    {
        return (aTex1->GetLayer() > aTex2->GetLayer());
    }

    CTextureManager::CTextureManager()
    {

    }

    CTextureManager::~CTextureManager()
    {
        for (CRenderable* lPointer : mRenderableList)
        {
            delete(lPointer);
        }
        mRenderableList.clear();
    }

    CRenderable* CTextureManager::CreateTexture(const json11::Json& aJSON, CGameObject* aGameObject, SDL_Renderer* aRenderer)
    {
        mRenderableList.push_back(new CRenderable(aGameObject));
        CRenderable* lRenderObject = mRenderableList.back();
        lRenderObject->Load(aJSON, aRenderer);
        std::sort(mRenderableList.begin(), mRenderableList.end(), SortTextureByLayers);
        return lRenderObject;
    }

    bool CTextureManager::DestroyTexture(const CRenderable* aTexture)
    {
        int lFound = -1;
        for (size_t i = 0; i< mRenderableList.size(); i++)
        {
            if (mRenderableList[i] == aTexture)
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
        for (std::vector< CRenderable* >::const_iterator lIt = mRenderableList.begin();
            lIt != mRenderableList.end();
            lIt++)
        {
            (*lIt)->OnRender(aRenderer);
        }
    }
}
