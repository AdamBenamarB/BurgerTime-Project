#pragma once
#include <vector>

#include "Component.h"
#include "RenderComponent.h"
#include "Structs.h"
#include "Transform.h"

namespace dae {
    class AnimatedRenderComponent;
    class CollisionComponent;

    class EnemyComponent : public Component
    {
    public:
        enum class State
        {
            left,
            right,
            up,
            down,
            stunned,
            falling,
            dead
        };
        EnemyComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float) override{}

        void SetPeter(GameObject* peterObj);// { m_Peter = peterObj; }

        void SetState(State state);// { m_State = state; }

        void InitAnimation(AnimatedRenderComponent* animComp, std::string textureLoc);

        void Kill();

        void Stun();

    private:
        void Initialize();
        void HandleMovement(float deltaTime);
        void HandleCollision(float deltaTime);
        void HandleAnim() const;
        void HandleStun(float deltaTime);
        State m_State = State::left;

        float m_Speed{ 60.f },//50 //30
            m_ClimbSpeed{ 40.f },
            m_FallSpeed{ 150.f };

        float m_StunTime{ 1.5f },
            m_StunElapsed{};

        bool m_OnPlatform{ false },
            m_OnLadder{ false },
            m_Horizontal{ false },
            m_Switched{ false };

        GameObject* m_Peter{};

        Vec2 m_Direction{};

        AnimatedRenderComponent* m_Anim{};

        //Anim
        int m_RunLeft{},
            m_RunRight{},
            m_Climb{},
            m_ClimbDown{},
            m_Stunned{};

        //Sound
        int m_Hit{},
            m_Fall{};

    };
}
