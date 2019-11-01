//==============================================================================
/*
    GameObject Class
    Hug Beneit
*/
//==============================================================================
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <json11/json11.hpp>
#include <utils/Vec2.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <CComponent.h>

namespace hugGameEngine
{
    class CGameObject : public CComponent
    {
    private:
        Vec2i                       mPosition               = Vec2i(0, 0);
        double                      mRotationAngle          = 0.f;
        Vec2                        mScale                  = Vec2( 1.f, 1.f );
        std::string                 mName                   = "";
        std::vector< CComponent* >  mComponentsList;

    public:
                        CGameObject     () : CComponent(this) { mComponentType = CComponent::EComponentType::E_GameObject; }
                       ~CGameObject     ()  {}
                        CGameObject     ( const CGameObject& aGo )    = delete;
        CGameObject&    operator=       ( const CGameObject& )        = delete;
        inline const Vec2i&                 GetPosition     () const                        { return mPosition; }
        inline void                         SetPosition     (const Vec2i& aPos)             { mPosition = aPos; }
        inline const double&                GetRotationAngle() const                        { return mRotationAngle; }
        inline const std::string            GetName         () const                        { return mName; }
        inline const Vec2&                  GetScale        () const                        { return mScale; }
        inline double                       GetDirection    () const                        { return mRotationAngle; }
        inline void                         SetDirection    (double aAngle)                 { mRotationAngle = aAngle; }
        void                                SetName         (const std::string& aName)      { mName = aName; }
        bool                                Load            (const json11::Json& aJSON) override;
        inline void                         AddComponent    (CComponent* aComponent)        { mComponentsList.push_back(aComponent); }
        inline std::vector< CComponent* >   GetComponentList()                              { return mComponentsList; }
        CComponent*                         FindFirstComponent(CComponent::EComponentType aType) const;
        std::vector< CComponent* >          FindAllComponents(CComponent::EComponentType aType) const;
        bool                                PointInGameObject(const SDL_Point& aPoint) const;

        template <class T>
        std::vector < T* > FindAllScript(const char* aScriptName) const
        {
            std::vector < T* > lRetVec;
            std::vector < CComponent* > lAllScripts = FindAllComponents(CComponent::EComponentType::E_Script);
            for (CComponent* lComponent : lAllScripts)
            {
                if (SDL_strcasecmp(dynamic_cast<CScript*>(lComponent)->GetScriptName(), aScriptName) == 0)
                {
                    lRetVec.push_back(dynamic_cast<T*>(lComponent));
                }
            }
            return lRetVec;
        }

        template <typename T>
        T* FindFirstScript(const char* aScriptName) const
        {
            std::vector < CComponent* > lAllScripts = FindAllComponents(CComponent::EComponentType::E_Script);
            for (CComponent* lComponent : lAllScripts)
            {
                if (SDL_strcasecmp(dynamic_cast<CScript*>(lComponent)->GetScriptName(), aScriptName) == 0)
                {
                    return dynamic_cast<T*>(lComponent);
                }
            }
            return nullptr;
        }
    };
}

#endif //__GAMEOBJECT_H_