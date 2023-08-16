#pragma once
#include "Component.h"
namespace dae {
    class PlatformComponent :
        public Component
    {
    public:
        PlatformComponent(GameObject* owner):Component{owner}{}

        void Update(float deltaTime) override{}
        void FixedUpdate(float deltaTime) override{}

        bool OnLeft(GameObject* go);
        bool OnRight(GameObject* go);
        bool OnBottom(GameObject* go);
    private:
        void CheckEdge();
        bool m_IsRightEdge = true;
        bool m_IsLeftEdge = true;
        bool m_CheckedEdge = false;

    };

}