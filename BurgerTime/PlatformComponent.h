#pragma once
#include "Component.h"
namespace dae {
    class PlatformComponent :
        public Component
    {
    public:
        PlatformComponent(GameObject* owner):Component{owner}{}

        void Update(float) override{}
        void FixedUpdate(float) override{}

        bool OnLeft(GameObject* go);
        bool OnRight(GameObject* go);
        bool OnBottom(GameObject* go);
        bool InRange(GameObject* go) const;

        float GetFloorY() const;
    private:
        void CheckEdge();
        bool m_IsRightEdge = true;
        bool m_IsLeftEdge = true;
        bool m_CheckedEdge = false;

    };

}