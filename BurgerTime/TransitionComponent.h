#pragma once
#include <vector>

#include "Component.h"
#include "RenderComponent.h"
#include "Transform.h"

namespace dae {
    class Scene;
    class CollisionComponent;

    class TransitionComponent : public Component
    {
    public:
        TransitionComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float deltaTime) override{}
        void SetTransitionTime(float time) { m_TransitionTime = time; }
        void SetReload(bool reload) { m_Reload = reload; }
    private:
        float m_TransitionTime{ 5.f },
            m_ELapsedTime{};

        bool m_Reload = false;
    };
}
