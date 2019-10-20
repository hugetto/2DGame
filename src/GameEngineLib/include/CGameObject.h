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
        bool                        mEnabled                = false;  //C++ 11 allows this initializaiton
        bool                        mPreviousFrameEnabled   = false;
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
        inline bool                         Enabled         () const                        { return mEnabled; }
        void                                OnCreate        ()                              {}
        void                                OnEnable        ()                              {}
        void                                OnDisable       ()                              {}
        void                                SetName         (const std::string& aName)      { mName = aName; }
        bool                                Load            (const json11::Json& aJSON);
        void                                Loop            (unsigned int aRenderTime);
        inline void                         AddComponent    (CComponent* aComponent)        { mComponentsList.push_back(aComponent); }
        inline std::vector< CComponent* >   GetComponentList()                              { return mComponentsList; }
        CComponent*                         FindFirstComponent(CComponent::EComponentType aType) const;
        std::vector< CComponent* >          FindAllComponents(CComponent::EComponentType aType) const;
        bool                                PointInGameObject(const SDL_Point* aPoint) const;
    };
}

#endif //__GAMEOBJECT_H_