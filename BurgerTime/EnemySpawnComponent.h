#pragma once
#include <vector>

#include "Component.h"
#include "RenderComponent.h"
#include "Transform.h"

namespace dae {
    class Scene;
    class CollisionComponent;

    class EnemySpawnComponent : public Component
    {
    public:
        EnemySpawnComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float deltaTime) override{}

    private:
        float m_TimePerSpawn{ 10.f },
            m_ELapsedTime{};
        GameObject* m_Peter{};
    };
}
