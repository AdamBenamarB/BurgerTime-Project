#pragma once
#include "Component.h"
#include "RenderComponent.h"

namespace dae {
    class AnimatedRenderComponent;
    class CollisionComponent;
    class Transform;
    //class AnimatedRenderComponent;

    class PlayerDogComponent : public Component
    {
    public:
        enum class State
        {
            idle,
            left,
            right,
            up,
            down,
            stunned,
            falling
        };
        PlayerDogComponent(GameObject* owner);
        ~PlayerDogComponent() {}
        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void SetState(State state);
        void ResetState();

        State GetState() const { return m_State; }
        void InitAnimation(AnimatedRenderComponent* comp);
        void SetOtherPeter(GameObject* peter) { m_OtherPeter = peter; }

        void Stun();
        void Initialize();
    private:
        float m_MovementSpeed = 80.f;
        Transform* m_Transform = nullptr;
        RenderComponent* m_RenderComp = nullptr;
        CollisionComponent* m_CollisionComp = nullptr;
        State m_State = State::idle;

        bool m_OnPlatform = false;
        bool m_OnLadder = false;

        float m_StunTime{ 1.5f },
            m_StunElapsed{};

        GameObject* m_OtherPeter = nullptr;

        //Sound
        int m_Fall{};

        //ANIM
        AnimatedRenderComponent* m_Anim{};


        int m_RunLeft{},
            m_RunRight{},
            m_Climb{},
            m_ClimbDown{},
            m_Stunned{};

        void HandleMovement(float deltaTime);
        void HandleAnim(float deltaTime);
        void HandleStun(float deltaTime);
        void CheckPeter();



    };
}