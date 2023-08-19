#pragma once

#include "Component.h"
#include "Subject.h"

namespace dae {
    class HealthComponent : public Component, public Subject
    {
    public:
        void Update(float) override {}
        void FixedUpdate(float) override {}
        HealthComponent(GameObject* owner) : Component(owner) {}
        int GetLives() { return m_Lives; }
        void SetLives(int lives) { m_Lives = lives; }
        void Hit(int amt = 1);
    private:
        int m_Lives = 4;
    };
}
