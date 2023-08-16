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

    private:
        float m_TransitionTime{ 5.f },
            m_ELapsedTime{};
    };
}
