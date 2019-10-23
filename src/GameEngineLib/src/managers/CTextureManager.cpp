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
            lPointer = 0;
        }
        mRenderableList.clear();
    }

    CRenderable* CTextureManager::CreateTexture(const json11::Json& aJSON, CGameObject* aGameObject)
    {
        mRenderableList.push_back(new CRenderable(aGameObject));
        CRenderable* lRenderObject = mRenderableList.back();
        lRenderObject->Load(aJSON);
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
            delete (aTexture);
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
            if ((*lIt)->ShouldCallOnEnable())
                (*lIt)->OnEnable();
            else if ((*lIt)->ShouldCallOnDisable())
                (*lIt)->OnDisable();
            (*lIt)->OnRender(aRenderer);
        }
    }

    CRenderable* CTextureManager::FindTextureByName(const char* aTextureName)
    {
        for (std::vector< CRenderable* >::iterator lIt = mRenderableList.begin();
            lIt != mRenderableList.end();
            lIt++)
        {
            if (SDL_strcmp(aTextureName, (*lIt)->GetName().c_str()))
                return (*lIt);
        }
        return nullptr;
    }

    std::vector< CRenderable* > CTextureManager::FindAllTextureByName(const char* aTextureName)
    {
        std::vector< CRenderable* > lRet;
        for (std::vector< CRenderable* >::iterator lIt = mRenderableList.begin();
            lIt != mRenderableList.end();
            lIt++)
        {
            if (SDL_strcmp(aTextureName, (*lIt)->GetName().c_str()))
                lRet.push_back(*lIt);
        }
        return lRet;
    }
}
